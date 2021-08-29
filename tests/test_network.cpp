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

#include <openssl/applink.c>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


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

 #define PORT "3490" // the 19
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




SCENARIO ("send raw IP packets (no matter if IPv4 or IPv6), using a raw IP socket",
          "[networking] [sockets]")
{
    GIVEN ("an address")
    {
        using namespace ph::network;
        
        Address auto address = const_str {"www.google.com"};
//        Port auto port = 80;
        auto port = "80";
        
        struct addrinfo hints
        {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
            .ai_flags = AI_PASSIVE
        };
        
        struct addrinfo *res, *p;
        
        int rv;
        
        rv = getaddrinfo (NULL, port, &hints, &res);
        
        if (rv != 0)
        {
            fprintf (stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            throw;
        }
        
        int sock;
        
        for (p = res; p != nullptr; p = p -> ai_next)
        {
            sock = socket (p -> ai_family, p -> ai_socktype, p -> ai_protocol);
            if (sock == -1)
            {
                perror ("server: socket");
                continue;
            }
            int yes;
            
           if ( setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
           {
               perror ("setsockopt");
           }
            
            
            if (bind (sock, p->ai_addr, p->ai_addrlen) == -1)
            {
                close (sock);
                perror ("server: bind");
                continue;
            }
            
            break;
        }
        
        freeaddrinfo (res);
        
        if (p==NULL)
        {
            fprintf(stderr, "server: failed to bind\n");
            exit(1);
        }
        
        if (listen (sock, BACKLOG) == -1)
        {
            perror ("listen");
            exit(1);
        }
        
        struct sigaction sa
        {
            .sa_handler = sigchld_handler,
            .sa_flags = SA_RESTART
        };
        
        if (sigaction (SIGCHLD, &sa, NULL) == -1)
        {
            perror ("sigaction");
            exit (1);
        }
        
        printf ("server: waiting for connections...\n");
        
        socklen_t sin_size;
        
        struct sockaddr_storage their_addr;
        
        int connected_sock;
        
        char s [INET6_ADDRSTRLEN];
        
        while (1)
        {
            sin_size = sizeof their_addr;
            connected_sock = accept (sock, (struct sockaddr *)&their_addr, &sin_size);
            if (connected_sock == -1)
            {
                perror("accept");
                continue;
            }
            
            inet_ntop (their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        
            printf ("server: got connection from %s\n", s);
            
            
            if (!fork ())
            { // this is the child process
                close (sock); // child doesn't need the listener i
                
                char buffer[30000] = {0};
                
                long valread = read (connected_sock , buffer, 30000);
                
                cout << valread << endl;
                cout << buffer << endl;
//                printf ("%s\n", buffer);
//                write(new_socket , hello , strlen(hello));
                auto msg =
                    "<!DOCTYPE html>"
                    "<html>"
                    "<body>"
                    "<h1>This is heading 1</h1>"
                    "<h2>This is heading 2</h2>"
                    "<h3>This is heading 3</h3>"
                    "<h4>This is heading 4</h4>"
                    "<h5>This is heading 5</h5>"
                    "<h6>This is heading 6</h6>"
                    "</body>"
                "</html>";
//                auto response = std::string {"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"};
                auto response = std::string {"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "} + std::to_string(strlen (msg)) + std::string {"\n\n"} + msg;

//                auto response = std::string {"POST /token HTTP/1.1"
//            "Host: oauth2.googleapis.com"
//            "Content-Type: application/x-www-form-urlencoded"
//
//            "code=4/P7q7W91a-oMsCeLvIaQm6bTrgtp7&"
//            "client_id=your_client_id&"
//            "client_secret=your_client_secret&"
//            "redirect_uri=https%3A//oauth2.example.com/code&"
//                "grant_type=authorization_code"};
                
                if (send (connected_sock, response.c_str(), response.size(), 0) == -1)
                {
                    perror("send");
                }
                
                close (connected_sock);
                exit(0);
                
            }
            close (connected_sock);
        }
        
//        Socket auto s = socket (PF_INET, SOCK_STREAM, 0);
        
        
//        fcntl (s, F_SETFL, O_NONBLOCK); // setting a socket to non-blocking
        
//        auto p = pollfd {0, POLLIN};
        
//        poll (&p, 1, -2);

        
//        Server auto server = [] (Address auto address, Port auto port)
//        {
//            return 2;
//
//        } (address, port);
        
        
        
//        auto sock_addr = sockaddr_in
//        {
//            .sin_family = AF_INET,
//            .sin_addr.s_addr = htonl(INADDR_ANY),
//            .sin_port = port
            
//        };
        
        
        
    }
}
