

file(GLOB_RECURSE HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library (ph_network
	${SOURCE_LIST}  ${HEADER_LIST} 
)

# target_sources (ph_network PRIVATE in/platform.hpp)
set (self ${PROJECT_NAME})

set_target_properties (${self} PROPERTIES CXX_STANDARD 20)
target_compile_features (${self} PUBLIC cxx_std_20)




# add_custom_target(
#     custom_header_target
#     DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/custom_header.h
# )
# ph_precompile (TARGET ph_concepts PRIVATE PCH ${std_pch} ${boost_pch})

add_library (ph::network ALIAS ph_network)
target_link_libraries (ph_network PUBLIC ${Boost_LIBRARIES})
target_include_directories (ph_network PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories (ph_network PUBLIC ${Boost_INCLUDE_DIRS})

target_compile_features (ph_network PUBLIC cxx_std_20)

target_compile_options(ph_network PUBLIC "-ast-dump  -fsyntax-only")


target_include_directories(ph_network PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ph_network>
    $<INSTALL_INTERFACE:include/ph_network>
)

target_include_directories(ph_network PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

else()
    set_target_properties(${PROJECT_NAME}          PROPERTIES FOLDER "dependencies")
endif()
