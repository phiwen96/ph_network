#include "test_network.hpp"









TEST_CASE("asio, connect to address and write string")
{
    using namespace std;
    cout << "hi" << endl;
    
    auto error_code = boost::system::error_code {};
    auto context = boost::asio::io_context {};
    auto endpoint = boost::asio::ip::tcp::endpoint {boost::asio::ip::make_address ("93.184.216.34", error_code), 80};
    auto socket = boost::asio::ip::tcp::socket {context};
    
    socket.connect (endpoint, error_code);
    
    REQUIRE_FALSE (error_code);
    REQUIRE (socket.is_open ());
    
    auto text = "GET /index.html HTTP/1.1\r\n"
                "Host: example.com\r\n"
                "Connection: close\r\n\r\n";

    
    socket.write_some (boost::asio::buffer (text, strlen (text)), error_code);
    
}


TEST_CASE ("main")
{
   
}
