cmake_minimum_required(VERSION 2.8.12)
project(live_wallpaper)

#include_directories(${live_wallpaper_SOURCE_DIR}/include)
include_directories(${live_wallpaper_SOURCE_DIR})

set(sources ${sources}
	include/live_wallpaper/live_wallpaper.hpp
	include/live_wallpaper/logger.hpp
	include/live_wallpaper/wallpaper.hpp
	include/live_wallpaper/wallpaper_storage.hpp
	src/live_wallpaper.cpp
	src/logger.cpp
	src/main.cpp
	src/wallpaper.cpp
	src/wallpaper_storage.cpp
	)
	
add_executable(live_wallpaper ${sources})
target_link_libraries(live_wallpaper ${CONAN_LIBS})
