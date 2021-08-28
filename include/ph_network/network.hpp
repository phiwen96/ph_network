#pragma once
#include <limits>
#include <numbers>

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif

//#include <boost/asio.hpp>

#include <iostream>
#include <ph_concepts/concepts.hpp>
#include <latch>
//#include <asio
//#include <boo
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include "common.hpp"
//#include <openssl/ssl.h>
//#include <openssl/err.h>

//#include <ph_concepts/concepts.hpp>

//#include
#include <poll.h>

using namespace ph::concepts;



namespace ph::network
{
    
    struct types {};
    
    
    auto host_to_nework (short i/*htons*/)
    {
        return htons (i);
    }

    auto host_to_nework (long i/*htonl*/)
    {
        return htonl (i);
    }
    


    
    auto network_to_host (short i/*ntohs*/)
    {
        return ntohs (i);
    }

    
    auto network_to_host (long i/*ntohl*/)
    {
        return ntohl (i);
    }
    
    
    
    
    template <typename...>
    struct socket;
    
    template <>
    struct socket <types>
    {
        
        
        constexpr auto begin () noexcept
        {
//            return
        }
    };
    
    
    
    template <typename T>
    concept Address = String <T>;
    
    template <typename T>
    concept Socket = std::is_convertible_v <T, int>;
    
    template <typename T>
    concept Port = std::is_convertible_v <T, unsigned short>;
}


