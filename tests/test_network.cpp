#include "test_network.hpp"
#include <poll.h>
#include <ph_network/network.hpp>


using std::cout, std::endl;




#include <unistd.h>
#include <sys/wait.h>

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




SCENARIO ("send raw IP packets (no matter if IPv4 or IPv6), using a raw IP socket",
          "[networking] [sockets]")
{
    GIVEN ("an address")
    {
        using namespace ph::network;
        
        Address auto address = "www.google.com";
        Port auto port = 80;
        
        
        
//        auto sock_addr = sockaddr_in
//        {
//            .sin_family = AF_INET,
//            .sin_addr.s_addr = htonl(INADDR_ANY),
//            .sin_port = port
            
//        };
        
        
        
    }
}
