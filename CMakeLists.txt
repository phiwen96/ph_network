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



function(Kiss)
	set(prefix ARG)
	set(NoValues Ja Nej)
	set(SingleValues Okej)
	set(MultiValues Lol Nope) 
	cmake_parse_arguments(${prefix} "${NoValues}" "${SingleValues}" "${MultiValues}" ${ARGN})
	if(ARG_Ja)
		message("lol")
	endif()
	
	foreach (noValue IN LISTS NoValues)
				# message ("${noValue}")

		if (${${prefix}_${noValue}})
			# message ("${noValue}")
		endif ()
	endforeach ()
	
endfunction(Kiss)


Kiss (Ja)


function(Bajs)
	set(prefix ARG)
	set(NoValues Ja Nej)
	set(SingleValues Ok)
	set(MultiValues Lol)
	cmake_parse_arguments(${prefix} "${NoValues}" "${SingleValues}" "{MultiValues}" ${ARGN})
	foreach(NoValue in LISTS NoValues)
		if(${${prefix}_${NoValue}})
			
		endif()
		
	endforeach()
	
endfunction(Bajs)
