cmake_minimum_required(VERSION 3.14)
project(texture_growing)


find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(texture_growing main.cpp grow_tools.cpp grow_tools.h)

target_link_libraries( texture_growing ${OpenCV_LIBS} )

