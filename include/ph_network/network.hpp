#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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
