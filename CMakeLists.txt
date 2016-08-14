# The main CMake setting

# Set project
project(iSVD)
cmake_minimum_required(VERSION 2.8)

# Set version number
set(ISVD_VERSION_MAJOR 0)
set(ISVD_VERSION_MINOR 1)
set(ISVD_VERSION_PATCH 0)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Add subdirectories
add_subdirectory(include)
add_subdirectory(demo)
