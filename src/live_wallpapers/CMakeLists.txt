cmake_minimum_required(VERSION 2.8.12)
project(live_wallpapers)

#include_directories(${live_wallpapers_SOURCE_DIR}/include)
include_directories(${live_wallpapers_SOURCE_DIR})

set(sources ${sources}
	include/live_wallpapers/live_wallpapers.hpp
	src/live_wallpapers.cpp
	src/main.cpp
	)
	
add_executable(live_wallpapers ${sources})
target_link_libraries(live_wallpapers ${CONAN_LIBS})
