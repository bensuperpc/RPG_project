cmake_minimum_required(VERSION 3.10)

project(convert_utils)

set(SRCS
	sfml_utils.cpp
	)
	
set(HEADERS
	sfml_utils.hpp
	)
	



#add_library(convert_utils_static STATIC ${SRCS} ${HEADERS})
add_library(convert_utils SHARED ${SRCS} ${HEADERS})
