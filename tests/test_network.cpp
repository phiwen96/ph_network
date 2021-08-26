#include "test_network.hpp"
#include <poll.h>
#include <ph_network/poll_server.hpp>


using std::cout, std::endl;

namespace ph::network
{

    
    TEST_CASE ()
    {
        
//        poll_server ();
    };
    
    TEST_CASE("asio, connect to address and write string")
    {
        using namespace std;
        
        
        const auto te0 = [](auto ip_address, Signed auto port)
        {
            cout << "hi" << endl;
            
        };
        
        
        te0 ("93.184.216.34", 80);
        
        
    }
    
    TEST_CASE ()
    {
        //        auto ctx = asio::io_context{};
        //        auto timer = asio::system_timer{ctx};
        //        timer.expires_from_now(1000ms);
        //        timer.async_wait([](auto error) { // Callback
        //        // Ignore errors..
        //        std::cout << "Hello from delayed callback\n";
        //        });
        //        std::cout << "Hello from main\n";
        //        ctx.run();
    }
}






TEST_CASE ("main")
{
    signed int a;
}

enum struct opcode
{
    MULTIPLY,
    DIVIDE,
    INCREMENT,
    DECREMENT,
    ADD,
    SUBTRACT,
    STOP,
    REPLAY
};

template <typename T>
struct stack
{
    
    std::vector <T> vec;
    
    
    
    auto top () -> auto&
    {
        return vec.back();
    }
    
    auto pop () -> auto&
    {
        vec.pop_back();
    }
    
    auto push (auto v)
    {
        vec.push_back(v);
    }
};

/**
 Number -> multiply, add, subtract, divide
 */

struct virtual_machine
{
    auto run (auto code, auto data)
    {
        for (auto c : code)
        {
            int a;
            int b;
            
            
            
            switch (c)
            {
                case opcode::MULTIPLY:
                {
                    
                    data.push (data.pop () * data.pop ());
                    
                    
                    break;
                }
                    
                case opcode::DIVIDE:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::INCREMENT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::DECREMENT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::ADD:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::SUBTRACT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::STOP:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::REPLAY:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                default:
                {
                    break;
                }
            }
        }
    }
};







TEST_CASE ("virtual machine")
{
    
    
    //    vm.run ({opcode::MULTIPLY}, {1, -70});
    
    
    
}


#include <unistd.h>
#include <sys/wait.h>

TEST_CASE("forking")
{
    cout << getpid() << endl;
    int i = 0;
    auto id = fork ();
    
    ++i;
    cout << i << endl;
    wait (NULL);
//    cout << id << endl;
}
