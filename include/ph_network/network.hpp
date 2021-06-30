#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


auto socket (addrinfo& a)
{
    return socket (a.ai_family, a.ai_socktype, a.ai_protocol);
}

auto to_string (addrinfo const& a )
{
    char* res = new char [INET6_ADDRSTRLEN];
    
    switch (a.ai_family)
    {
        case AF_INET:
        {
            auto* ip = (sockaddr_in*) a.ai_addr;
            auto* addr = &ip -> sin_addr;
            inet_ntop (AF_INET, addr, res, sizeof (char) * INET6_ADDRSTRLEN);
            return res;
        }
            
        case AF_INET6:
        {
            auto* ip = (sockaddr_in*) a.ai_addr;
            auto* addr = &ip -> sin_addr;
            inet_ntop (AF_INET6, addr, res, sizeof (char) * INET6_ADDRSTRLEN);
            return res;
        }
    }
}



template <int>
struct _IP_v;

template <>
struct _IP_v <4>
{
    
};


template <>
struct _IP_v <6>
{
    
};


template <int i>
constexpr auto IP_v = _IP_v <i> {};


template <typename = short>
auto host_to_network_byte_order ();


template <>
auto host_to_network_byte_order <short> ()
{
    
}

template <>
auto host_to_network_byte_order <long> ()
{
    
}

template <typename = short>
auto network_to_host_byte_order ();


template <>
auto network_to_host_byte_order <short> ()
{
    
}

template <>
auto network_to_host_byte_order <long> ()
{
    
}



template <int I>
auto create_socket (auto&& domain, auto&& type, auto&& protocol)
{
    
}

/// associates a socket with a socket address structure,
/// i.e a specified local port number and ip address.
auto bind_to_port (auto&& socket, auto&& port/**/)
{
    
}

/// causes a bound tcp socket to enter listening mode.
auto listen ()
{
    
}

/// accepts a received incoming attempt to create a new tcp connection
/// from the remote client. and creates a new socket associated with the
/// socket address pair of this connection.
auto accept ()
{
    
}
