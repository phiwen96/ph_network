#include "test_network.hpp"

#include <ph_network/network.hpp>
#include <const_str/const_str.hpp>

#include <array>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vulkan/vulkan.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <vector>

#define PORT "80"
//#include <openssl/applink.c>
//#include <openssl/bio.h>
//#include <openssl/ssl.h>
//#include <openssl/err.h>


using std::cout, std::endl;






auto do_work ()
{
    sleep (rand () % 4);
}
template <unsigned>
struct A;

template <>
struct A <0>
{};

template <>
struct A <1>
{};

template <>
struct A <2> : A <0>
{};

template <>
struct A <3> : A <0>, A <1>
{};



TEST_CASE ("The Empty Base Class Optimization (EBCO)")
{
    REQUIRE (sizeof (A <0>) == sizeof (A <3>));
}

TEST_CASE("forking")
{
    //    cout << getpid() << endl;
    //    int i = 0;
    //    auto id = fork ();
    
    //    ++i;
    //    cout << i << endl;
    //    wait (NULL);
    //    cout << id << endl;
}

#include <sys/socket.h>
#include <netinet/in.h>

SCENARIO ("networking")
{
    
    SECTION ("webserver")
    {
        auto server_fd = int {0};
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            return 0;
        }
    }
    
    SECTION ("send raw IP packets (no matter if IPv4 or IPv6), using a raw IP socket")
    {
        int soc = socket (PF_INET, SOCK_RAW, IPPROTO_IP);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

//#define PORT "3490" // the 19
#define BACKLOG 10 // how 21
void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}

// get sockaddr, IPv4 or
void *get_in_addr(struct sockaddr * sa)
{
    if (sa->sa_family == AF_INET){
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int get_listener_socket (void)
{
    
    int listener; // Listening socket descriptor
    int yes=1; // For setsockopt() SO_REUSEADDR, below int rv;
    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    // Get us a socket and bind it
    int rv;
    
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    //    continue; }
    // Lose the pesky "address already in use" error message
    for(p = ai; p != NULL; p = p->ai_next)
    {
        listener = socket (p->ai_family, p->ai_socktype, p->ai_protocol);
        
        if (listener < 0)
        {
            continue;
        }
        
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }
        
        break;
    }
    
    
    freeaddrinfo(ai); // All done with this 65
                      // If we got here, it means we didn't get bound
    if(p==NULL)
    {
        return -1;
    }
    
    // Listen
    if (listen(listener, 10) == -1)
    {
        return -1;
    }
    
    return listener;
}

auto encode (auto number)
{
    
}

auto decode (auto number)
{
    
}

int sendall (int s, char* buf, int* len)
{
    
    int total = 0;
    int bytesleft = *len;
    int n;
    
    while(total < *len)
    {
        n = send (s, buf+total, bytesleft, 0);
        
        if (n == -1)
        {
            break;
        }
        
        total += n;
        bytesleft -= n;
    }
    
    *len = total; // return number actually sent here
    return n==-1?-1:0; // return -1 on failure, 0 on success }
}
TEST_CASE ()
{
    // Listening socket descriptor
    int listener;
    int newfd;
    struct sockaddr_storage remoteaddr; // Client address socklen_t addrlen;
    
    
    char buf[256]; // Buffer for client data
    char remoteIP[INET6_ADDRSTRLEN];
    socklen_t addrlen;
    // Start off with room for 5 connections // (We'll realloc as necessary)
    //    int fd_count = 0;
    //    int fd_size = 5;
    //    struct pollfd *pfds = (pollfd*) malloc(sizeof *pfds * fd_size); // Set up and get a listening socket
    auto pfds = std::vector <pollfd> {};
    
    listener = get_listener_socket();
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n"); exit(1);
    }
    // Add the listener to set
    pfds.push_back (pollfd {listener, POLLIN});
    //    pfds[0].fd = listener;
    //    pfds[0].events = POLLIN; // Report ready to read on incoming connection
    //    fd_count = 1; // For the listener
    // Main loop
    for(;;)
    {
        int poll_count = poll (pfds.data(), pfds.size(), -1);
        
        if (poll_count == -1)
        {
            perror("poll");
            exit(1);
            
        }
        // Run through the existing connections looking for data to read
        for(int i = 0; i < pfds.size(); i++)
        {
            // Check if someone's ready to read
            if (pfds[i].revents & POLLIN)
            { // We got one!!
                if (pfds[i].fd == listener) {
                    // If listener is ready to read, handle new connection
                    addrlen = sizeof remoteaddr;
                    newfd = accept (listener,(struct sockaddr *)&remoteaddr, &addrlen);
                    
                    if (newfd == -1)
                    {
                        perror("accept");
                        
                    }
                    else
                    {
                        //                    add_to_pfds(&pfds, newfd, &pfds, &fd_size);
                        //                    pfds.emplace_back (newfd, POLLIN);
                        pfds.push_back (pollfd {newfd, POLLIN});
                        printf("pollserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN),
                               newfd);
                    }
                    auto msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                    write (newfd, msg, strlen (msg));
                }
                else
                {
                    // If not the listener, we're just a regular client
                    int nbytes = recv (pfds[i].fd, buf, sizeof buf, 0);
                    int sender_fd = pfds[i].fd;
                    if (nbytes <= 0)
                    {
                        if (nbytes == 0)
                        {
                            // Got error or connection closed by client if (nbytes == 0) {
                            // Connection closed
                            printf ("pollserver: socket %d hung up\n", sender_fd);
                        }
                        else
                        {
                            perror ("recv");
                        }
                        
                        //                        send (<#int#>, <#const void *#>, <#size_t#>, <#int#>)
                        
                        close (pfds[i].fd); // Bye!
                        pfds.erase(pfds.begin() + i);
                        //                del_from_pfds(pfds, i, &fd_count);
                        
                    } else
                    {
                        // We got some good data from a client
                        for(int j = 0; j < pfds.size(); j++)
                        { // Send to everyone!
                            int dest_fd = pfds[j].fd;
                            // Except the listener and ourselves
                            if (dest_fd != listener && dest_fd != sender_fd)
                            {
                                
                                auto msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                                cout << msg << endl;
                                //                                if (send (dest_fd, msg, strlen (msg), 0) == -1)
                                //                                {
                                //                                    perror("send");
                                //
                                //                                }
                                write (dest_fd, msg, strlen (msg));
                            }
                            
                        }
                    }
                } // END handle data from client
            } // END got ready-to-read from poll() } // END looping through file descriptors
        } // END for(;;)--and you thought it would never end! return 0;
    }
}
