#pragma once

#include <type_traits>
#include <stdio.h>
#include <memory>
//#include <boost/asio.hpp>



#define fwd(x) std::forward <decltype (x)> (x)



//template <typename T>
//concept Socket = same_as <T, boost::asio::ip::tcp::socket>;



char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
//        std::exit(74);
    }
    
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    
    char* buffer = (char*)std::malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
//        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';
    
    fclose(file);
    return buffer;
}








