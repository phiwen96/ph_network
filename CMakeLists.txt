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
	set (NoValues DONT_ERASE_MODULE_IF_NOT_DEFINED)
	set (SingleValues NAME INCLUDE SRC)
	set (MultiValues MODULES BAJS)

	cmake_parse_arguments (${prefix} "${NoValues}" "${SingleValues}" "${MultiValues}" ${ARGN})

	if (ARG_NAME)
		# message (${ARG_NAME})
	endif ()

	if (ARG_INCLUDE AND ARG_SRC)
		message (${ARG_INCLUDE})
	endif ()

	# foreach (single_value IN LISTS SingleVal)
		
	# endforeach ()
	

	if (ARG_SRC)
		message (${ARG_SRC})
	endif ()

	if (ARG_MODULES)
		foreach (module_name IN LISTS ARG_MODULES)
			set (header_file "${ARG_INCLUDE}/${module_name}.hpp")
			set (source_file "${ARG_SRC}/${module_name}.cpp")
			if (EXISTS ${header_file})
				# message("${header_file} already exists.")
			else ()
				message("creating ${header_file}")
				file (WRITE "${header_file}" "#pragma once")
			endif ()
			if (EXISTS ${source_file})
				# message("${source_file} already exists.")
			else ()
				message("creating ${header_file}")
				file (WRITE "${source_file}" "#include \"${module_name}\"")
			endif ()
		endforeach ()
	endif ()

	if (NOT DONT_ERASE_MODULE_IF_NOT_DEFINED)
		file (GLOB include "${ARG_INCLUDE}/*.hpp")
		file (GLOB src "${ARG_SRC}/*.cpp")

	# else ()
		foreach (file ${include})
			list (FIND ARG_MODULES "${file}" _index)
			if (${_index} GREATER -1)
				message("maybe delete ${file}?")
			endif()
			# if (${file} IN LISTS ARG_MODULES)
				# message("maybe delete ${file}=")
			# endif ()
			
			# message("jj ${file}")
		endforeach ()
		
		
	endif ()
	
	

	
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
		# "Bajs"

	INCLUDE
		"${CMAKE_CURRENT_LIST_DIR}/include/pp_network"

	SRC
		"${CMAKE_CURRENT_LIST_DIR}/src"
)




# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode && cmake --open xbuild