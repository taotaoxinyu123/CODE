#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include "boost/format.hpp"
#include "cocc_upper_client_recv.h"
#include "cocc_his_impl.h"
#include "cocc_common.h"
#include "cocc_common_json.h"
#include "cocc_frame.hpp"
#include "cocc_tick_tock.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace {

    // 记录日志
    static void Log(const std::string& message)
    {
        hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
    }

    // 处理接收到的数据；flat_buffer为空表示无write；非空则需write
    static void DealResponse(const beast::flat_buffer& buffer_read);

    // Report a failure
    static void fail(beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    // Sends a WebSocket message and prints the response
    class session : public std::enable_shared_from_this<session>
    {
        tcp::resolver resolver_;
        websocket::stream<beast::tcp_stream> ws_;
        beast::flat_buffer buffer_read_;
        std::string host_;

    public:
        // Resolver and socket require an io_context
        explicit session(net::io_context& ioc)
            : resolver_(net::make_strand(ioc))
            , ws_(net::make_strand(ioc))
        {
        }

        // Start the asynchronous operation
        void run(char const* host, char const* port)
        {
            // Save these for later
            host_ = host;

            // Look up the domain name
            resolver_.async_resolve(host, port,
                beast::bind_front_handler(
                    &session::on_resolve,
                    shared_from_this()));
        }

        void on_resolve(beast::error_code ec, tcp::resolver::results_type results)
        {
            if (ec) return fail(ec, "resolve");

            // Set the timeout for the operation
            beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(1));

            // Make the connection on the IP address we get from a lookup
            beast::get_lowest_layer(ws_).async_connect(results,
                beast::bind_front_handler(
                    &session::on_connect,
                    shared_from_this()));
        }

        void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
        {
            if (ec) return fail(ec, "connect");

            // Turn off the timeout on the tcp_stream, because
            // the websocket stream has its own timeout system.
            beast::get_lowest_layer(ws_).expires_never();

            // Set suggested timeout settings for the websocket
            ws_.set_option(
                websocket::stream_base::timeout::suggested(
                    beast::role_type::client));

            // Set a decorator to change the User-Agent of the handshake
            ws_.set_option(websocket::stream_base::decorator(
                [](websocket::request_type& req)
                {
                    req.set(http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-async");
                }));

            // Update the host_ string. This will provide the value of the
            // Host HTTP header during the WebSocket handshake.
            // See https://tools.ietf.org/html/rfc7230#section-5.4
            host_ += ':' + std::to_string(ep.port());

            // Perform the websocket handshake
            ws_.async_handshake(host_, "/",
                beast::bind_front_handler(
                    &session::on_handshake,
                    shared_from_this()));
        }

        void on_handshake(beast::error_code ec)
        {
            if (ec) return fail(ec, "handshake");

            // Send the message
            hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
            hconfig::Config config = ci.config();
            std::string tt = "";
            ws_.async_write(net::buffer(tt.c_str(), tt.size()),
                beast::bind_front_handler(
                    &session::on_read,
                    shared_from_this()));
        }

        void on_read(beast::error_code ec, std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if (ec) return fail(ec, "on_read");

            buffer_read_.clear();
            // Read a message into our buffer
            ws_.async_read(buffer_read_,
                beast::bind_front_handler(
                    &session::on_temp,
                    shared_from_this()));
        }

        void on_temp(beast::error_code ec, std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if (ec) return fail(ec, "on_temp");
            DealResponse(buffer_read_);  // 解析读取到的数据
            on_read(ec, bytes_transferred);
        }

    };

    void do_uppper_client_recv()
    {
        // sleep 10ms
        std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        hconfig::Config config = ci.config();
        while (true)
        {
            // The io_context is required for all I/O
            net::io_context ioc;
            // Launch the asynchronous operation
            std::make_shared<session>(ioc)->run(
                config.cocc_upper_recv.ip.c_str(),
                boost::lexical_cast<std::string>(config.cocc_upper_recv.port).c_str());
            // Run the I/O service. The call will return when
            // the socket is closed.
            ioc.run();
        }
    }
    void DealResponse(const beast::flat_buffer& buffer_read)
    {
        std::size_t size = buffer_read.size();
        if (0 == size) return;  // #End

        auto cb = buffer_read.cdata();
        std::vector<char> recv;
        recv.resize(size + 1, 0x00);
        memcpy(&recv.at(0), cb.data(), size);
        try
        {
            rapidjson::Document document;
            if (document.Parse(&recv.at(0)).HasParseError())
            {
                // 解析错误
                Log(boost::lexical_cast<std::string>(document.GetParseError()));
                return;
            }
            int type = 0, schedule_type = 0;
            if (!hcommon::GetJsonInt(document, "msg_id", type)) return;  // #End

            hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
            if (hdata::his_data_type::E_TICK_TOCK == static_cast<hdata::his_data_type>(type))
            {
                hclient::TickTock(document);
            }
            else if (hdata::his_data_type::E_REPORT_BEGIN == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportBegin(document);
            }
            else if (hdata::his_data_type::E_GROUP_RUNNING_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportGroupRunning(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_GROUP_RUNNING_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_DRIVER_DISTANCE_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportDriverDistance(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_DISPATCHER_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportDisPatcher(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_DISPATCHER_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_GROUP_BAK_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportGroupBak(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_GROUP_BAK_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_GROUP_STATUS_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportGroupStatus(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_GROUP_STATUS_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_ACTION_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportAction(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_ACTION_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_ALARM_REPORT == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportAlarm(document);
                ci.push_mid_data_string_impl(hdata::his_data_type::E_ALARM_REPORT, &recv.at(0));
            }
            else if (hdata::his_data_type::E_INUSED_SCHEDULE == static_cast<hdata::his_data_type>(type))
            {
                if (!hcommon::GetJsonInt(document, "sub_id", schedule_type)) return;  // #End
                if (hdata::tg_driver_type::E_TG_DRIVER_START == static_cast<hdata::his_data_type>(schedule_type)) 
                {
                    hclient::ScheduleBegin(document);
                }
                else if (hdata::tg_driver_type::E_TG_DRIVER_RUNNING == static_cast<hdata::his_data_type>(schedule_type))
                {
                    hclient::ScheduleInused(document);
                    ci.push_mid_data_string_impl(hdata::his_data_type::E_INUSED_SCHEDULE, &recv.at(0));
                }
                else if (hdata::tg_driver_type::E_TG_DRIVER_END == static_cast<hdata::his_data_type>(schedule_type))
                {
                    hclient::ScheduleEnd(document);
                }
                else 
                {
                    Log("通道数据回复 type error:" + std::to_string(type));
                }
            }
            else if (hdata::his_data_type::E_HISTORY_SCHEDULE == static_cast<hdata::his_data_type>(type))
            {
                if (!hcommon::GetJsonInt(document, "sub_id", schedule_type)) return;  // #End
                if (hdata::tg_driver_type::E_TG_DRIVER_START == static_cast<hdata::his_data_type>(schedule_type))
                {
                    hclient::ScheduleBegin(document);
                }
                else if (hdata::tg_driver_type::E_TG_DRIVER_RUNNING == static_cast<hdata::his_data_type>(schedule_type))
                {
                    hclient::SchedulActual(document);
                    ci.push_mid_data_string_impl(hdata::his_data_type::E_HISTORY_SCHEDULE, &recv.at(0));
                }
                else if (hdata::tg_driver_type::E_TG_DRIVER_END == static_cast<hdata::his_data_type>(schedule_type))
                {
                    hclient::ScheduleEnd(document);
                }
                else
                {
                    Log("通道数据回复 type error:" + std::to_string(type));
                }
            }
            else if (hdata::his_data_type::E_REPORT_END == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportEnd(document);
            }
            else if (hdata::his_data_type::E_REPORT_NACK == static_cast<hdata::his_data_type>(type))
            {
                hclient::ReportNoNack(document);
            }
            else
            {
                Log("通道数据回复 type error:" + std::to_string(type));
            }
        }
        catch (std::exception& ex)
        {
            Log(ex.what());
        }
    }

} // namesapce

void start_upper_client_recv()
{
    std::thread* uppper_recv_thread = new std::thread(&do_uppper_client_recv);
}
