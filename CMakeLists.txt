# The main CMake setting

# Set project
project(MCNLA)
cmake_minimum_required(VERSION 2.8)
set(MCNLA_NAME "Monte Carlo Numerical Linear Algebra Package")

# Set version number
set(MCNLA_VERSION_MAJOR 0)
set(MCNLA_VERSION_MINOR 4)
set(MCNLA_VERSION_PATCH 0)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Sets the options
include(cmake/options.cmake)

# Sets the compile flags
include(cmake/flags.cmake)

# Add subdirectories
add_subdirectory(doxygen)
add_subdirectory(demo)
add_subdirectory(check)

# Create configure files
include(cmake/configure.cmake)

# Sets install rule
include(cmake/install.cmake)

# Display message
include(cmake/display.cmake)
