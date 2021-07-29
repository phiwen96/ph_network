cmake_minimum_required(VERSION 3.18)
project(ph_network CXX)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set (CMAKE_CXX_STANDARD 20)
	set (CMAKE_CXX_STANDARD_REQUIRED ON)
	set (CMAKE_CXX_EXTENSIONS ON)
	set_property (GLOBAL PROPERTY USE_FOLDERS ON)
	find_package (Boost 1.74 REQUIRED)
	# find_package(OpenSSL REQUIRED)
endif()
if (NOT TARGET ph_cmake)
	include (FetchContent)
	FetchContent_Declare(
  		ph_cmake
  		GIT_REPOSITORY https://github.com/phiwen96/ph_cmake.git
  		GIT_TAG        v0.0.0)

	FetchContent_GetProperties(ph_cmake)
	
	if (NOT ph_cmake_POPULATED)
  		FetchContent_Populate (ph_cmake)
  		add_subdirectory (${ph_cmake_SOURCE_DIR} ${ph_cmake_BINARY_DIR})
	endif ()
endif ()

ph_fetch (USER "phiwen96" REPOS "ph_concepts" "ph_system")











ph_create_modules (

	MODULES 
		"network"
		"common"

	INCLUDE
		"${CMAKE_CURRENT_LIST_DIR}/include/ph_network"

	SRC
		"${CMAKE_CURRENT_LIST_DIR}/src"
)




# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode && cmake --open xbuild
# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode