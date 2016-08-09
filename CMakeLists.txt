# The main CMake setting

# Set project
project(iSVD)
cmake_minimum_required(VERSION 3.0)

# Set version number
set(ISVD_VERSION_MAJOR 0)
set(ISVD_VERSION_MINOR 0)
set(ISVD_VERSION_PATCH 0)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -Wall -Wextra -Wpedantic")

# Set include directories
include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_BINARY_DIR}/include")

# Add subdirectories
add_subdirectory(include)
add_subdirectory(demo)
