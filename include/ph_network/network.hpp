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
        total_bytes_written += socket.write_some (boost::asio::buffer (msg.c_str() + total_bytes_written, msg.length() - total_bytes_written));
    }
}



namespace ph
{
    
    
    
    
    
#define _KEYBOARD \
X (newline, '\n') \
X (tab, '\t') \
X (backspace, '\b') \
X (backslash, '\\') \
X (nullChar, '\0')
    enum struct keyboard
    {
#define X(a, ...) a,
        _KEYBOARD
#undef X
        undefined
//        newline,
//        tab,
//        backspace,
//        backslash,
//        nullChar
//        auto operator=(keyboard const& o)
//        {
//            return
//        }
    };
    
    auto operator== (char const& c, keyboard const& k) -> bool
    {
        #define X(a, b, ...) \
                if (k == keyboard::a and c == b) return true;
        _KEYBOARD
        #undef X
                else
                {
                    return false;
                }
    }
    
    auto operator== (keyboard const& k, char const& c) -> bool
    {

#define X(a, b, ...) \
        if (k == keyboard::a and c == b) return true;

_KEYBOARD
#undef X
        else
        {
            return false;
        }
    }
    
    namespace network
    {
        
//        template <typename protocol>
//        struct application_layer;
//
//        template <>
//        struct application_layer <>
//        {
//
//        };
//        namespace internet_protocol
        template <typename Application_layer, typename Transport_layer, typename Internet_layer, typename Link_layer>
        struct internet_protocol
        {
            Application_layer application_layer;
            Transport_layer transport_layer;
            Internet_layer internet_layer;
            Link_layer link_layer;
        };
        
        template <typename Application_layer, typename Transport_layer, typename Internet_layer, typename Link_layer>
        internet_protocol (Application_layer, Transport_layer, Internet_layer, Link_layer) ->  internet_protocol <Application_layer, Transport_layer, Internet_layer, Link_layer>;
        
        
        
        auto socket ()
        {
            return ::socket (AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        }
        
        
//        template <template <typename...> typename Container = std::vector>
        auto toIpAddresses (char const* str, auto& addresses)
        {
//            auto addresses = Container <char const*> {};
            auto ipstr = (char*) std::malloc (INET6_ADDRSTRLEN * sizeof (char));
            auto err = int {};

            auto hints = addrinfo
            {
                .ai_family = AF_UNSPEC,
                .ai_socktype = SOCK_STREAM
            };
            
            addrinfo* res;
            
            if ((err = getaddrinfo (str, nullptr, &hints, &res)) != 0)
            {
                fprintf (stderr, "getaddrinfo: %s\n", gai_strerror(err));
                exit (EXIT_FAILURE);
            }
            
            for (auto* p = res; p != nullptr; p = p -> ai_next)
            {
                void* addr;
                
                switch (p -> ai_family)
                {
                    case AF_INET:
                    {
                        auto* ipv4 = (sockaddr_in*) p -> ai_addr;
                        addr = &(ipv4 -> sin_addr);
                        break;
                    }
                    case AF_INET6:
                    {
                        auto* ipv6 = (sockaddr_in6*) p -> ai_addr;
                        addr = &(ipv6 -> sin6_addr);
                        break;
                    }
                    default:
                    {
                        throw ("whaaat");
                    }
                }
//                inet_ntop(<#int#>, <#const void *#>, <#char *#>, <#socklen_t#>)
                inet_ntop (p -> ai_family, addr, ipstr, INET6_ADDRSTRLEN * sizeof (char));
                addresses.push_back (ipstr);
            }
            
            freeaddrinfo (res);
            return addresses;
        }
    }
    
    
    
    
    
    namespace file
    {
        
    }
    
    
}


