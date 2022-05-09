#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include "boost/format.hpp"
#include "cocc_upper_client_send.h"
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

    // 常规任务规划；输出需write的flat_buffer
    static void ScheduleTask(beast::flat_buffer& buffer_write);

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
            std::string tt = hframe::frame_tick_tock_t(
                hcommon::SimpleTime(),
                hdata::his_data_type::E_TICK_TOCK, 
                "0.1",
                "tick").pack();
            ws_.async_write(net::buffer(tt.c_str(), tt.size()),
                beast::bind_front_handler(
                    &session::on_write,
                    shared_from_this()));
        }

        void on_write(beast::error_code ec, std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if (ec) return fail(ec, "read");
            beast::flat_buffer buffer_write;
            ScheduleTask(buffer_write);
            // 0 < buffer_write.size()
            // Send the message
            ws_.async_write(net::buffer(buffer_write.cdata()),
                beast::bind_front_handler(
                    &session::on_write,
                    shared_from_this()));
        }
    };

    void do_uppper_client_send()
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
                config.cocc_upper_send.ip.c_str(),
                boost::lexical_cast<std::string>(config.cocc_upper_send.port).c_str());
            // Run the I/O service. The call will return when
            // the socket is closed.
            ioc.run();
        }
    }

    void ScheduleTask(beast::flat_buffer& buffer_write)
    {
        buffer_write.clear();
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        hticktock::Clock& ti = hticktock::singleton_clock::get_mutable_instance();
        std::string version = "1";
        while (true) 
        {
            std::string now = hcommon::SimpleTime();
            bool flag = false;
            std::string line_id;
            std::string start_time, end_time;
            std::string date;            
            // request data - from trigger
            ci.get_request_group_running_tunnel_his(flag, line_id);
            if (flag)
            {
                Log("request_group_running_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_report_ask_t(now, hdata::his_data_type::E_REPORT_ASK, version, line_id, "01", hdata::statistics_report_type::E_GROUP_RUNNING, "").pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, false);
                break;
            }
            ci.get_request_driver_distance_tunnel_his(flag, line_id);
            if (flag)
            {
                Log("request_driver_distance_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_report_ask_t(now, hdata::his_data_type::E_REPORT_ASK, version, line_id, "02", hdata::statistics_report_type::E_DRIVER_DISTANCE, "").pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, false);
                break;
            }
            ci.get_request_dispatcher_tunnel_his(flag, line_id);
            if (flag)
            {
                Log("request_dispatcher_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_report_ask_t(now, hdata::his_data_type::E_REPORT_ASK, version, line_id, "03", hdata::statistics_report_type::E_DISPATHCHER, "").pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_DISPATCHER_REPORT, false);
                break;
            }
            ci.get_request_group_bak_tunnel_his(flag, line_id);
            if (flag)
            {
                Log("request_group_bak_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_report_ask_t(now, hdata::his_data_type::E_REPORT_ASK, version, line_id, "04", hdata::statistics_report_type::E_GROUP_BAK, "").pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_GROUP_BAK_REPORT, false);
                break;
            }
            ci.get_request_group_status_tunnel_his(flag, line_id);
            if (flag)
            {
                Log("request_group_status_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_report_ask_t(now, hdata::his_data_type::E_REPORT_ASK, version, line_id, "05", hdata::statistics_report_type::E_GROUP_STATUS, "").pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, false);
                break;
            }
            ci.get_request_action_tunnel_his(flag, line_id, start_time, end_time);
            if (flag)
            {
                Log("request_action_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_alarm_ask_t(now, hdata::his_data_type::E_ALARM_ACK, version, line_id, "06", hdata::action_msg_type::E_ACTION_MSG, start_time, end_time).pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_ACTION_REPORT, false);
                break;
            }
            ci.get_request_alarm_tunnel_his(flag, line_id, start_time, end_time);
            if (flag)
            {
                Log("request_alarm_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_alarm_ask_t(now, hdata::his_data_type::E_ALARM_ACK, version, line_id, "07", hdata::action_msg_type::E_ALARM_MSG, start_time, end_time).pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_ALARM_REPORT, false);
                break;
            }
            ci.get_request_schedual_inused_tunnel_his(flag, line_id, date);
            if (flag)
            {
                Log("request_schedual_inused_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_schedule_ask_t(now, hdata::his_data_type::E_LOAD_HISTORY_TG_DATA, version, line_id, "08", date, hdata::tg_msg_type::E_TG_PLAN).pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_INUSED_SCHEDULE, false);
                break;

            }
            ci.get_request_schedual_actual_tunnel_his(flag, line_id, date);
            if (flag)
            {
                Log("request_schedual_actual_tunnel");
                hcommon::String2FlatBuffer(
                    hframe::frame_schedule_ask_t(now, hdata::his_data_type::E_LOAD_HISTORY_TG_DATA, version, line_id,  "09", date,  hdata::tg_msg_type::E_TG_ACTUAL).pack(), buffer_write);
                ci.set_request_flag_his(hdata::his_data_type::E_HISTORY_SCHEDULE, false);
                break;
            }
            // ticktock
            if (ti.is_enable_start_tick_tock()) 
            {
                hcommon::String2FlatBuffer(
                    hframe::frame_tick_tock_t(now, hdata::his_data_type::E_TICK_TOCK, version, "tick").pack(), buffer_write);
                break;
            }
            if (0 < buffer_write.size())
            {
                break;  // #End
            }
            // sleep 100ms
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(100));
            // request data - from time
        }
    }


} // namesapce

void start_upper_client_send()
{
    std::thread* uppper_send_thread = new std::thread(&do_uppper_client_send);
}
