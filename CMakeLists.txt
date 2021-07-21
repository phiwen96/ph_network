cmake_minimum_required(VERSION 3.18)
project(ph_network CXX)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set (CMAKE_CXX_STANDARD 20)
	set (CMAKE_CXX_STANDARD_REQUIRED ON)
	set (CMAKE_CXX_EXTENSIONS ON)
	set_property (GLOBAL PROPERTY USE_FOLDERS ON)
	find_package (Boost 1.74 REQUIRED)
	find_package(OpenSSL REQUIRED)
endif()
if (NOT TARGET phake)
	add_subdirectory (cmake/phake)
endif ()
if (NOT TARGET ph_concepts)
	add_subdirectory (dependencies/ph_concepts)
endif ()
if (NOT TARGET ph_system)
	add_subdirectory (dependencies/ph_system)
endif ()
add_subdirectory(src)
add_subdirectory(tests)




function (ph_build_library)

	set (prefix ARG)
	set (NoValues SNOPP)
	set (SingleValus NAME INCLUDE_DST SRC_DST)
	set (MultiValues MODULES BAJS)

	cmake_parse_arguments (${prefix} "${NoValues}" "${SingleValues}" "${MultiValues}" ${ARGN})

	if (ARG_NAME)
		# message (${ARG_NAME})
	endif ()

	if (ARG_INCLUDE_DST)
		# message (${ARG_INCLUDE_DST})
	endif ()

	if (ARG_SRC_DST)
		# message (${ARG_SRC_DST})
	endif ()

	if (ARG_MODULES)
		foreach (value IN LISTS ARG_MODULES)
			# message("kiss ${value}")
		endforeach ()
	endif ()
	
	foreach (type IN LISTS MultiValues)
		if (${prefix}_${type})
			foreach(value IN LISTS ${prefix}_${type})
				# message("${value}")
			endforeach()
		endif()
	endforeach ()
	
endfunction ()




ph_build_library (
	NAME 
		"pp_network" 

	MODULES 
		"Floating"
		"Integer"
		"Number" 
		"Range" 
		"String"

	INCLUDE_DST 
		"${CMAKE_CURRENT_LIST_DIR}/include/pp_network"

	SRC_DST
		"${CMAKE_CURRENT_LIST_DIR}/src"
)