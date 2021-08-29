#pragma once
#include <limits>
#include <numbers>
#include <iostream>
#include <ph_concepts/concepts.hpp>
#include <latch>
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
    
    
    
    
//    template <typename...>
//    struct socket;
//
//    template <>
//    struct socket <types>
//    {
//
//
//        constexpr auto begin () noexcept
//        {
////            return
//        }
//    };
    
    
    
    template <typename T>
    concept Address = String <T>;
    
    template <typename T>
    concept Socket = std::is_convertible_v <T, int>;
    
    template <typename T>
    concept Port = std::is_convertible_v <T, unsigned short>;
    
    template <typename T>
    concept Server = requires ()
    {
        true;
    };
}


auto poll_server ()
    {
        struct pollfd pfds[1]; // More if you want to monitor more
        pfds[0].fd = 0; // Standard input
        pfds[0].events = POLLIN; // Tell me when ready to read
        
        int num_events = poll (pfds, 1, 2500); // 2.5 second timeout
        
        std::cout << "tjo" << std::endl;
        if (num_events == 0) { printf("Poll timed out!\n");
        } else {
            int pollin_happened = pfds[0].revents & POLLIN;
            if (pollin_happened) {
                printf("File descriptor %d is ready to read\n", pfds[0].fd);
            } else {
                printf("Unexpected event occurred: %d\n", pfds[0].revents);
            } }
    }

