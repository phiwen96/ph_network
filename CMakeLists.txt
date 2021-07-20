cmake_minimum_required(VERSION 3.18)

project(ph_network CXX)

set (CMAKE_CXX_STANDARD 20)

find_package (Boost 1.75 REQUIRED)
find_package(OpenSSL REQUIRED)
# sudo apt-get install libssl-dev

# brew install openssl
# cmake -DOPENSSL_ROOT_DIR=/opt/homebrew/Cellar/openssl@1.1/1.1.1k -DOPENSSL_LIBRARIES=/opt/homebrew/Cellar/openssl@1.1/1.1.1k/lib

add_subdirectory(cmake/phake)

add_subdirectory(src)
add_subdirectory(tests)
