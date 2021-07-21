cmake_minimum_required(VERSION 3.18)

project(ph_network CXX)

set (CMAKE_CXX_STANDARD 20)

find_package (Boost 1.74 REQUIRED)
find_package(OpenSSL REQUIRED)
# sudo apt-get install libssl-dev

include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v2.13.1)

# FetchContent_GetProperties(Catch2)

# if(NOT Catch2_POPULATED)
# 	FetchContent_Populate(Catch2)
	# add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})
# endif()

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)



# brew install openssl
# cmake -DOPENSSL_ROOT_DIR=/opt/homebrew/Cellar/openssl@1.1/1.1.1k -DOPENSSL_LIBRARIES=/opt/homebrew/Cellar/openssl@1.1/1.1.1k/lib

add_subdirectory(cmake/phake)

add_subdirectory(src)
add_subdirectory(tests)
