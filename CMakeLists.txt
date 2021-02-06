cmake_minimum_required(VERSION 3.17)
project(ean_13)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ean_13 main.cpp ean_13.h ean_13.cpp resources.h ean_13_constant.h)
target_link_libraries(ean_13 ${OpenCV_LIBS})