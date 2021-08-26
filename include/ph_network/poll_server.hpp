#include <poll.h>
#include <iostream>
#include "common.hpp"

namespace ph::network
{
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
}
