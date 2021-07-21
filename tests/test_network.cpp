#include <ph_concepts/concepts.hpp>

#include <catch2/catch.hpp>

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif

#include <boost/asio.hpp>


//#include <ph_network/network.hpp>
//#include <thread>
//using namespace std::literals::string_literals;
//
//template <typename T, auto x>
//std::ostream& operator<< (std::ostream& os, std::array<T, x> const& a)
//{
//    os << "{ ";
//    for (auto i : a)
//    {
//        os << i << " ";
//    }
//    os << "}";
//
//    return os;
//}
//
//template <typename T>
//std::ostream& operator<< (std::ostream& os, std::vector<T> const& a)
//{
//    os << "{ ";
//    for (auto i : a)
//    {
//        os << i << " ";
//    }
//    os << "}";
//
//    return os;
//}
//
//using namespace std;
//
//#define _PROCESS \
//    X(creation_unsuccessfull) \
//    X(child) \
//    X(anon_id)
//
//enum class PROCESS
//{
//#define X(p, ...) p,
//    _PROCESS
//#undef X
//};
//
//
//
//
//
//
//auto process (auto builder) -> PROCESS
//{
////    auto p = fork ();
//
//
//
//}
//
//using std::cout;
//using std::endl;
////using ph::operator==;
//
//auto operator"" _hej(char const*){
//    return 2;
//}
//
////TEST_CASE ("ph::keyboard")
////{
////    REQUIRE (ph::keyboard::backslash != 'k');
////    REQUIRE (ph::keyboard::backslash == '\\');
////
////    REQUIRE ('k' != ph::keyboard::backslash);
////    REQUIRE ('\\' == ph::keyboard::backslash);
////}
//
//template <auto...>
//struct layer
//{
//
//};
//
//consteval auto operator "" _transport_layer (char const* str, std::size_t n)
//{
////    return 2;
//    int h = 0;
//    for(int i = 0; i < n; ++i)
//    {
//        ++h;
//    }
//    return h;
//}
//
//template <auto a>
//auto stri = std::string {a};
//
//
//template <typename T>
//concept Hash = std::is_same_v <std::hash, T> and requires (T t)
//{
//    true;
//};
//
//template <typename T>
//concept Nonce = requires (T, T) // nummer som bara används en gång
//{
//    requires not requires(T n1, T n2) {
//        n2 = n1;
//    };
//    true;
//};
//
////template <typename >
//
//template <typename T>
//concept Node = requires ()
//{
//    true;
//};
//
//auto send (Node auto from, Node auto to)
//{
//
//}
//
//auto contact (Node auto from, Node auto to)
//{
//
//}
//
//
//auto challange (auto from, auto to) -> Nonce auto
//{
//
//}
//
//auto respond (Hash auto, Node auto from, Node auto challanger)
//{
//
//}
//
//auto hash_function (auto&& password, Nonce auto&&)
//{
//    return password;
//}
//
//



TEST_CASE("asio, connect to address and write string")
{
    using namespace std;
    cout << "hi" << endl;
    
    auto error_code = boost::system::error_code {};
    auto context = boost::asio::io_context {};
    auto endpoint = boost::asio::ip::tcp::endpoint {boost::asio::ip::make_address ("93.184.216.34", error_code), 80};
    auto socket = boost::asio::ip::tcp::socket {context};
    
    socket.connect (endpoint, error_code);
    
    REQUIRE_FALSE (error_code);
    REQUIRE (socket.is_open ());
    
    auto text = "GET /index.html HTTP/1.1\r\n"
                "Host: example.com\r\n"
                "Connection: close\r\n\r\n";

    
    socket.write_some (boost::asio::buffer (text, strlen (text)), error_code);
    
}
