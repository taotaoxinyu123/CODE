#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <list>
#include "cocc_lower_server.h"
#include "cocc_his_impl.h"
#include "cocc_common.h"
#include "cocc_common_json.h"
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace posix = boost::posix_time;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

static void Log(const std::string& message)
{
    hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
}
// 响应第三方客户端端请求；成功返回true
bool DealRequest(const beast::flat_buffer& buffer_read, std::list<beast::flat_buffer>& buffer_write);

// Report a failure
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Echoes back all received WebSocket messages
class session : public std::enable_shared_from_this<session>
{
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::list<beast::flat_buffer> buffer_write;

public:
    // Take ownership of the socket
    explicit
        session(tcp::socket&& socket)
        : ws_(std::move(socket))
    {

    }
    // Get on the correct executor
    void run()
    {
        net::dispatch(ws_.get_executor(),
            beast::bind_front_handler(
                &session::on_run,
                shared_from_this()));
    }
    // Start the asynchronous operation
    void on_run()
    {
        // Set suggested timeout settings for the websocket
        ws_.set_option(
            websocket::stream_base::timeout::suggested(
                beast::role_type::server));
        // Set a decorator to change the Server of the handshake
        ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-async");
            }));
        // Accept the websocket handshake
        ws_.async_accept(
            beast::bind_front_handler(
                &session::on_accept,
                shared_from_this()));
    }

    void on_accept(beast::error_code ec)
    {
        if (ec)
            return fail(ec, "accept");
        // Read a message
        do_read();
    }

    void do_read()
    {
        // Read a message into our buffer
        ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }

    void on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);
        // This indicates that the session was closed
        if (ec == websocket::error::closed)
            return;

        if (ec)
            fail(ec, "read");
        // 逻辑处理
        Log("收到消息");
        bool success = DealRequest(buffer_, buffer_write);
        // Echo the message
        ws_.text(ws_.got_text());
        ws_.async_write(
            buffer_write.front().data(),
            beast::bind_front_handler(
                &session::on_write,
                shared_from_this()));
    }

    void  on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);
        if (ec)
            return fail(ec, "write");
        // send others
        buffer_write.erase(buffer_write.begin());
        if (!buffer_write.empty())
            ws_.async_write(
                buffer_write.front().data(),
                beast::bind_front_handler(
                    &session::on_write,
                    shared_from_this()));
        // Clear the buffer
        buffer_.consume(buffer_.size());
        // Do another read
        do_read();
    }
};

class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

public:
    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint)
        : ioc_(ioc)
        , acceptor_(ioc)
    {
        beast::error_code ec;
        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec)
        {
            fail(ec, "open");
            return;
        }
        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if (ec)
        {
            fail(ec, "set_option");
            return;
        }
        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec)
        {
            fail(ec, "bind");
            return;
        }
        // Start listening for connections
        acceptor_.listen(
            net::socket_base::max_listen_connections, ec);
        if (ec)
        {
            fail(ec, "listen");
            return;
        }
    }
    // Start accepting incoming connections
    void  run()
    {
        do_accept();
    }

private:
    void do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket)
    {
        if (ec)
        {
            fail(ec, "accept");
        }
        else
        {
            auto ip = socket.remote_endpoint().address().to_string();
            std::cout << ip << " connected." << std::endl;
            // Create the session and run it
            std::make_shared<session>(std::move(socket))->run();
        }
        // Accept another connection
        do_accept();
    }
};

void do_lower_server()
{
    hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
    hconfig::Config config = ci.config();
    auto const address = net::ip::make_address(config.cocc_lower.ip.c_str());
    auto const port = static_cast<unsigned short>(std::atoi(boost::lexical_cast<std::string>(config.cocc_lower.port).c_str()));
    auto const threads = std::max<int>(1, std::atoi(boost::lexical_cast<std::string>(config.cocc_lower.client_max_num).c_str()));
    // The io_context is required for all I/O
    net::io_context ioc_server{ threads };
    // Create and launch a listening port
    std::make_shared<listener>(ioc_server, tcp::endpoint{ address, port })->run();
    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve((size_t)threads - 1);
    for (auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc_server]
            {
                ioc_server.run();
            });
    ioc_server.run();
}

void start_lower_server()
{
    std::thread* lower_thread = new std::thread(&do_lower_server);
}

// 处理请求
bool DealRequest(const beast::flat_buffer& buffer_read, std::list<beast::flat_buffer>& buffer_write) 
{
    std::size_t size = buffer_read.size();
    if (0 == size) return false;  // #End
    auto cb = buffer_read.cdata();
    std::vector<char> recv;
    recv.resize(size + 1, 0x00);
    memcpy(&recv.at(0), cb.data(), size);
    std::string text = &recv.at(0);
    try
    {
        rapidjson::Document document;
        document.Parse(text.c_str());
        int type = 0, schedule_type = 0;
        if (!hcommon::GetJsonInt(document, "msg_id", type)) return false;

        if (hdata::his_data_type::E_REPORT_ASK == static_cast<hdata::his_data_type>(type))
        {
            hserver::ReportAsk(document, buffer_write);
        }
        else if (hdata::his_data_type::E_ALARM_ACK == static_cast<hdata::his_data_type>(type))
        {
            hserver::AlarmAsk(document, buffer_write);
        }
        else if (hdata::his_data_type::E_LOAD_HISTORY_TG_DATA == static_cast<hdata::his_data_type>(type))
        {
            hserver::ScheduleAsk(document, buffer_write);
        }
        else
        {
            Log("第三方请求数据，没找到类型" + std::to_string(type));
            return false;
        }
    }
    catch (std::exception& ex)
    {
        Log(ex.what());
        return false;
    }
    return true;
}