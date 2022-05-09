#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/lexical_cast.hpp>
#include "boost/format.hpp"
#include "cocc_publish_client.h"
#include "cocc_publish_impl.h"
#include "cocc_config_container.hpp"
#include "cocc_publish_frame.hpp"
#include "cocc_publish_common.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace {

    // 记录日志
    static void Log(const std::string& message)
    {
        pubdata::singleton_coccpublish_impl::get_mutable_instance().logger().Log(message);
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
            ws_.async_handshake(host_, "/center_slave_send",
                beast::bind_front_handler(
                    &session::on_handshake,
                    shared_from_this()));
        }

        void on_handshake(beast::error_code ec)
        {
            if (ec) return fail(ec, "handshake");
            // Send the message
            std::list<pubdata::real_data_type> msg_id_arr;
            msg_id_arr.push_back(pubdata::real_data_type::TRAIN_BLOCK_INFO);
            msg_id_arr.push_back(pubdata::real_data_type::CBTC_TRAIN_INDICATION_INIT);
            std::string tt = pframe::frame_client_id("publish_iplat", msg_id_arr).pack();
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
            ws_.binary(ws_.got_binary());
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

    void do_start_publish()
    {
        // sleep 10ms
        std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
        pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
        pconfig::Config config = pi.config();
        while (true)
        {
            // The io_context is required for all I/O
            net::io_context ioc;
            // Launch the asynchronous operation
            std::make_shared<session>(ioc)->run(
                config.machine.ip.c_str(),
                std::to_string(config.machine.port).c_str());
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
        recv.resize(size, 0x00);
        memcpy(&recv.at(0), cb.data(), size);
        try
        {
            if (recv.size() < 2) 
            {
                Log("DealResponse：recv收到数据长度小于2");
                return;
            }
            // type
            int type = recv[0];
            // data
            std::size_t d_size = recv.size() - 1;
            std::vector<char> data;
            data.resize(d_size, 0x00);
            memcpy(&data.at(0), &recv.at(1), d_size);
            if (pubdata::real_data_type::TRAIN_BLOCK_INFO == static_cast<pubdata::real_data_type>(type))
            {
                pclient::TrainBlockInfo(type, data);
            }
            else if (pubdata::real_data_type::CBTC_TRAIN_INDICATION_INIT == static_cast<pubdata::real_data_type>(type))
            {
                pclient::CbtcTrainIndicationInit(type, data);
            }
            else 
            {
                Log("DealResponse：msg_id类型错误");
            }
        }
        catch (std::exception& ex)
        {
            Log(ex.what());
        }
     }

} // namesapce

void start_publish()
{
    std::thread* uppper_recv_thread = new std::thread(&do_start_publish);
}
