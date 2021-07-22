#pragma once

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif

#include <boost/asio.hpp>

#include <iostream>
#include <ph_concepts/concepts.hpp>

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include "common.hpp"
//#include <openssl/ssl.h>
//#include <openssl/err.h>

#include <ph_concepts/concepts.hpp>



namespace ph::network
{
    
    auto test_0 = [](String auto address = "93.184.216.34", Signed auto port = 80)
    {
        auto error_code = boost::system::error_code {};
        auto context = boost::asio::io_context {};
        auto endpoint = boost::asio::ip::tcp::endpoint {boost::asio::ip::make_address (address), port};
        auto sock = boost::asio::ip::tcp::socket {context};
        
        sock.connect (endpoint, error_code);
        
        if (not error_code)
        {
            std::cout << "Success!" << std::endl;
        } else
        {
            std::cout << "'Failed to connect to address!!! " << error_code.message () << std::endl;
        }
        
      //   auto context = boost::
    };
}


