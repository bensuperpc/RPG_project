cmake_minimum_required(VERSION 3.11)

project(utils)

set(SRCS
	#sfml/screen_save.cpp
	opengl/screen_save.cpp
	date/date.cpp
	opengl/screen_save.c
	)
	
set(HEADERS
	#sfml/screen_save.hpp
	date/date.hpp
	opengl/screen_save.hpp
	opengl/screen_save.h
	)
	

#add_library(utils_static STATIC ${SRCS} ${HEADERS})
add_library(utils SHARED ${SRCS} ${HEADERS})
