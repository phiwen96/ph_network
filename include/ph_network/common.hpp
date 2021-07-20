#pragma once

#include <type_traits>
#include <boost/asio.hpp>


#define fwd(x) std::forward <decltype (x)> (x)

template <typename T, typename U>
concept same_as = std::is_same_v <T, U>;

template <typename T, typename U>
concept convertible_to = std::is_convertible_v <T, U>;


template<typename T>
struct string_type : std::false_type
{
    
};

template <typename T, size_t SZ>
struct string_type <T [SZ]> : std::true_type// partial specialization for arrays of known bounds
{
    
};

template <typename T, size_t SZ>
struct string_type <T (&) [SZ]> : std::true_type// partial spec. for references to arrays of known bounds
{
    
};

template <typename T>
struct string_type <T (&) []> : std::true_type // partial spec. for references to arrays of unknown bounds
{
    
};

template <typename T>
struct string_type <T*> : std::true_type // partial specialization for pointers
{
    
};




template <typename T>
concept Number = std::is_integral_v <T>;

template <typename T>
concept String = string_type <T>::value or requires (T& A, T& B, int i)
{
    {A [i]} -> convertible_to <char&>;
    //    {B [i]} -> convertible_to <char>;
    {A.size ()} -> convertible_to <std::size_t>;
    true;
};



template <typename T>
concept Socket = same_as <T, boost::asio::ip::tcp::socket>;



char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }
    
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';
    
    fclose(file);
    return buffer;
}
