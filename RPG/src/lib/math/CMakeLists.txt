cmake_minimum_required(VERSION 3.11)

project(math C CXX)

set(SRCS
	getGravitationalAttraction_imp.hpp
	getSchwarzschild_imp.hpp
	sphere_imp.hpp
	cylinder_imp.hpp
	power_imp.hpp
	power.c
	)
	
set(HEADERS
	getGravitationalAttraction.hpp
	getSchwarzschild.hpp
	sphere.hpp
	cylinder.hpp
	constant.hpp
	power.hpp
	power.h
	)

#add_library(math_static STATIC ${SRCS} ${HEADERS})
add_library(math SHARED ${SRCS} ${HEADERS})

#install (TARGETS math DESTINATION bin)
#install (FILES math.h DESTINATION include)
