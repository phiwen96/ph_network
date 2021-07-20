#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include "common.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>

namespace ph::network
{
    
    auto test_0 = []()
    {
        auto error_code = boost::system::error_code {};
        auto context = boost::
    };
}


