
//#define RUN_CATCH

#if defined (RUN_CATCH)

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>




auto main (int argc, char* argv[]) -> int
{
    int result = Catch::Session().run( argc, argv );
    return result;
}

#else

#include <ph_network/network.hpp>
#include <thread>

auto server = [](char const* port)
{
    addrinfo* servinfo;
    int s;
    
    auto hints = addrinfo
    {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE
    };
    
    if (auto err = getaddrinfo (nullptr, port, &hints, &servinfo); err != 0)
    {
        
        fprintf (stderr, "getaddrinfo error: %s\n", gai_strerror (err));
        exit (1);
    }
    
    auto* p = servinfo;
    
    for (; p != nullptr; p = p -> ai_next)
    {
        if ((s = socket (p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror ("server: socket");
            continue;
        }
        auto yes = 1 ;
        if (setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
        {
            perror ("setsockopt");
            exit (1);
        }
        if (bind (s, p->ai_addr, p->ai_addrlen) == -1)
        {
            close (s);
            perror ("server: bind");
            continue;
        }
        
        break;
    }
    
    freeaddrinfo (servinfo);
    
    if (p == nullptr)
    {
        std::cout << "Server failed to bind." << std::endl;
        exit (1);
    }
    
    
    //    fcntl (s, F_SETFL, O_NONBLOCK); // set to non-blocking
    //    fcntl (s, F_SETFL, O_ASYNC); // set to asynchronous I/O

    if (listen (s, 10) == -1)
    {
        throw;
    }
    
    std::cout << "server: waiting for connections..." << std::endl;
    
    while (true)
    {
        auto their_addr = sockaddr_storage {};
        auto addr_size = socklen_t {sizeof (their_addr)};
        //    std::cout << "kuk" << std::endl;
        auto their_socket = accept (s, (struct sockaddr*) &their_addr, &addr_size);
        std::cout << "kuk" << std::endl;
        
        if (their_socket < 0)
        {
            throw;
        }
        
        char buf [1024];
        
        if (read (their_socket, buf, 1024) < 0)
        {
            throw;
        }
        std::cout << "server::got_message(\"" << buf << "\")" << std::endl;
        //    std::cout << buf << std::endl;
        
        auto msg = "Hello from server.";
        
        write (their_socket, msg, strlen (msg));
    }
    
    
    
    //    close (s);
    
    
    
    //    auto addr_size = sizeof their_addr;
    
};

auto client = [](char const* address = nullptr, char const* port = "8080")
{
    addrinfo* res;
    
    auto hints = addrinfo
    {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        //        .ai_flags = AI_PASSIVE
    };
    
    if (auto err = getaddrinfo (address, port, &hints, &res); err != 0)
    {
        
        fprintf (stderr, "getaddrinfo error: %s\n", gai_strerror (err));
        exit (1);
    }
    auto s = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if (s == -1)
    {
        perror ("socket");
        exit (1);
    }
    
    auto err = connect (s, res->ai_addr, res->ai_addrlen);
    
    //    std::cout << "kuk" << std::endl;
    if (err == -1)
    {
        //        fprintf (stderr, "getaddrinfo error: %s\n", gai_strerror (err));
        throw;
        //        exit(1);
    }
    //    std::cout << "kuk" << std::endl;
    
    auto msg = "Hello from client!";
    
    send (s, msg, strlen (msg), 0);
    
    close (s);
    
    //    std::byte buf [1024];
    //
    //    if (read (s, buf, 1024) < 0)
    //    {
    //        throw;
    //    }
    
    
    //    return;
    
    freeaddrinfo (res);
    
    //    std::cout << "yo" << std::endl;
    
};


auto main (int argc, char* argv[]) -> int
{
    auto th1 = std::thread{[](){
        server (/*port*/"8080");
    }};
    auto th2 = std::thread{[](){
        
        for (int i = 0; i < 10; ++i)
        {
            client (/*address*/"localhost", /*port*/"8080");
        }
        std::cout << "client" << std::endl;
    }};
    
    th1.join ();
    th2.join ();
}


#endif

