#pragma once

#include <type_traits>


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


template <typename T, typename U>
concept convertible_to = std::is_convertible_v <T, U>;

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
