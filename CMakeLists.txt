cmake_minimum_required(VERSION 3.18)
project(ph_network CXX)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set (CMAKE_CXX_STANDARD 20)
	set (CMAKE_CXX_STANDARD_REQUIRED ON)
	set (CMAKE_CXX_EXTENSIONS ON)
	set_property (GLOBAL PROPERTY USE_FOLDERS ON)
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

if (NOT TARGET ph_concepts)
	include (FetchContent)
	FetchContent_Declare(
  		ph_concepts
  		GIT_REPOSITORY https://github.com/phiwen96/ph_concepts.git
  		GIT_TAG        v0.0.0)

	FetchContent_GetProperties(ph_concepts)
	
	if (NOT ph_concepts_POPULATED)
  		FetchContent_Populate (ph_concepts)
  		add_subdirectory (${ph_concepts_SOURCE_DIR} ${ph_concepts_BINARY_DIR})
	endif ()
endif ()

macro(Fetch )
 	set(options OPTIONAL FAST)
    set(oneValueArgs TARGET)
    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments (LOL "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

	if (NOT LOL_TARGET)
		message (FATAL_MESSAGE "please specify target")
	endif ()

	if (NOT LOL_TAG)
		set (LOL_TAG "v0.0.0")
	endif ()

	if (NOT LOL_REPO)
		set (LOL_REPO "https://github.com/phiwen96/${LOL_TARGET}.git")
	else()
		set (LOL_REPO "https://github.com/${LOL_REPO}/${LOL_TARGET}.git")
	endif()


	include (FetchContent)

	FetchContent_Declare(
  		${LOL_TARGET}
  		GIT_REPOSITORY ${LOL_REPO}
  		GIT_TAG        ${LOL_TAG})

	FetchContent_GetProperties (${LOL_TARGET})
	
	if (NOT ${LOL_TARGET}_POPULATED)
  		FetchContent_Populate (${LOL_TARGET})
  		add_subdirectory (${${LOL_TARGET}_SOURCE_DIR} ${${LOL_TARGET}_BINARY_DIR})
	endif ()
	
						
	
endmacro(Fetch)

Fetch (TARGET ph_data_structures)




# ph_fetch_git_repos (USER "phiwen96" REPOS "ph_concepts" "ph_system")

# ph_create_modules (

# 	MODULES 
# 		"network"
# 		"common"

# 	INCLUDE
# 		"${CMAKE_CURRENT_LIST_DIR}/include/ph_network"

# 	SRC
# 		"${CMAKE_CURRENT_LIST_DIR}/src"
# )

add_subdirectory (src)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory (tests)
endif ()


# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode && cmake --open xbuild
# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode