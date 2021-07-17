#include <catch2/catch.hpp>
#include <ph_network/network.hpp>
using namespace std::literals::string_literals;

template <typename T, auto x>
std::ostream& operator<< (std::ostream& os, std::array<T, x> const& a)
{
    os << "{ ";
    for (auto i : a)
    {
        os << i << " ";
    }
    os << "}";
    
    return os;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T> const& a)
{
    os << "{ ";
    for (auto i : a)
    {
        os << i << " ";
    }
    os << "}";
    
    return os;
}

using namespace std;

#define _PROCESS \
    X(creation_unsuccessfull) \
    X(child) \
    X(anon_id)

enum class PROCESS
{
#define X(p, ...) p,
    _PROCESS
#undef X
};






auto process (auto builder) -> PROCESS
{
//    auto p = fork ();
    

    
}

using std::cout;
using std::endl;
//using ph::operator==;

auto operator"" _hej(char const*){
    return 2;
}

TEST_CASE ("ph::keyboard")
{
    REQUIRE (ph::keyboard::backslash != 'k');
    REQUIRE (ph::keyboard::backslash == '\\');
    
    REQUIRE ('k' != ph::keyboard::backslash);
    REQUIRE ('\\' == ph::keyboard::backslash);
}

template <auto...>
struct layer
{
    
};

consteval auto operator "" _transport_layer (char const* str, std::size_t n)
{
//    return 2;
    int h = 0;
    for(int i = 0; i < n; ++i)
    {
        ++h;
    }
    return h;
}

template <auto a>
auto stri = std::string {a};


template <typename T>
concept Hash = std::is_same_v <std::hash, T> and requires (T t)
{
    true;
};

template <typename T>
concept Nonce = requires (T, T) // nummer som bara används en gång
{
    requires not requires(T n1, T n2) {
        n2 = n1;
    };
    true;
};

//template <typename >

template <typename T>
concept Node = requires ()
{
    true;
};

auto send (Node auto from, Node auto to)
{
    
}

auto contact (Node auto from, Node auto to)
{
    
}


auto challange (auto from, auto to) -> Nonce auto
{
    
}

auto respond (Hash auto, Node auto from, Node auto challanger)
{
    
}

auto hash_function (auto&& password, Nonce auto&&)
{
    return password;
}

auto server = [](char const* port)
{
    addrinfo* res;
    
    auto hints = addrinfo
    {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE
    };
    
    if (auto err = getaddrinfo (nullptr, port, &hints, &res); err != 0)
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
    
    fcntl (s, F_SETFL, O_NONBLOCK); // set to non-blocking
    fcntl (s, F_SETFL, O_ASYNC); // set to asynchronous I/O
    
    auto yes = 1;
    
    if (auto err = setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (yes)); err == - 1)
    {
        perror ("sockopt");
        exit (1);
    }
    
//    char hostname[128];
//    gethostname(hostname, sizeof hostname);
//    printf("My hostname: %s\n", hostname);
    
    bind (s, res->ai_addr, res->ai_addrlen);
    
    if (listen (s, 10) == -1)
    {
        throw;
    }
    
    
    struct sockaddr_storage their_addr;
    socklen_t addr_size {sizeof their_addr};
    
    auto their_socket = accept (s, (sockaddr*) &their_addr, &addr_size);
    
    if (their_socket < 0)
    {
        throw;
    }
    
    std::byte buf [1024];
    
    
    if (read (their_socket, buf, 1024) < 0)
    {
        throw;
    }
    
    auto msg = "Hello from server.";
    
    write (their_socket, msg, strlen (msg));
    
    
    
    
    
//    auto addr_size = sizeof their_addr;
    
    freeaddrinfo (res);
};

TEST_CASE ("Server")
{
    server (/*port*/"80");
}

TEST_CASE ("Client")
{
    return;
    addrinfo* res;
    
    auto hints = addrinfo
    {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE
    };
    
    if (auto err = getaddrinfo ("www.example.net", "8080", &hints, &res); err != 0)
    {
        
        fprintf (stderr, "getaddrinfo error: %s\n", gai_strerror (err));
        exit(1);
    }
    
    auto s = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if (auto err = connect (s, res->ai_addr, res->ai_addrlen); err == -1)
    {
        fprintf (stderr, "getaddrinfo error: %s\n", gai_strerror (err));
        throw;
        exit(1);
    }
    
    
    freeaddrinfo (res);
}



//
//
//
TEST_CASE ("Constructs and assignments")
{
    std::cout << "hi" << std::endl;
}
