cmake_minimum_required(VERSION 3.18)

project(ph_network CXX)

set (CMAKE_CXX_STANDARD 20)

find_package (Boost 1.75 REQUIRED)



add_subdirectory(src)
