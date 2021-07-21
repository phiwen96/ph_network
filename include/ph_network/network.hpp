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




namespace ph::network
{
    
    auto test_0 = [](auto address, auto port)
    {
        auto error_code = boost::system::error_code {};
        auto context = boost::asio::io_context {};
        auto endpoint = boost::asio::ip::tcp::endpoint {boost::asio::ip::make_address (address), port};
        
        
        
      //   auto context = boost::
    };
}


