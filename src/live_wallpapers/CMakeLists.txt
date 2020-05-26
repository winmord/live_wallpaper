cmake_minimum_required(VERSION 2.8.12)
project(live_wallpapers)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

#include_directories(${live_wallpapers_SOURCE_DIR}/include)
include_directories(${live_wallpapers_SOURCE_DIR})

set(sources ${sources}
	include/live_wallpapers/hello.hpp
	src/hello.cpp
	)
	
add_executable(live_wallpapers ${sources})
target_link_libraries(live_wallpapers ${CONAN_LIBS})

# CTest is a testing tool that can be used to test your project.
# enable_testing()
# add_test(NAME example
#          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#          COMMAND example)
