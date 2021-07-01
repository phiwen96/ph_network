#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include "common.hpp"

auto write (Socket auto&& socket, String auto&& msg)
{
    auto total_bytes_written = size_t {0};

    while (total_bytes_written != msg.length())
    {
        total_bytes_written += socket.write_some (buffer (msg.c_str() + total_bytes_written, msg.length() - total_bytes_written));
    }
}
