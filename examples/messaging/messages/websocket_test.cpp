#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;

int main() {
    try {
        // Setup context and resolver
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        websocket::stream<tcp::socket> ws(ioc);

        // Resolve echo.websocket.events (public echo test server)
        auto const results = resolver.resolve("echo.websocket.events", "80");

        // Connect to server
        net::connect(ws.next_layer(), results.begin(), results.end());

        // Perform WebSocket handshake
        ws.handshake("echo.websocket.events", "/");

        // Make a JSON message
        nlohmann::json msg;
        msg["message"] = "Hello from Appwrite C++ SDK test!";
        
        // Send it
        ws.write(net::buffer(msg.dump()));

        // Read back the echo
        beast::flat_buffer buffer;
        ws.read(buffer);

        std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;

        // Close connection
        ws.close(websocket::close_code::normal);
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
