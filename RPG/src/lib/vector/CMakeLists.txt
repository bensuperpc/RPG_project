cmake_minimum_required(VERSION 3.11)

project(vector C CXX)

set(SRCS
	vector.cpp
	)
	
set(HEADERS
	vector.hpp
	vector_imp.hpp
	)

#add_library(math_static STATIC ${SRCS} ${HEADERS})
add_library(vector SHARED ${SRCS} ${HEADERS})

#install (TARGETS math DESTINATION bin)
#install (FILES math.h DESTINATION include)
