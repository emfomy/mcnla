# The main CMake setting

# Set project
project(MCNLA)
cmake_minimum_required(VERSION 3.0)
set(MCNLA_NAME "Monte Carlo Numerical Linear Algebra Package")

# Set version number
set(MCNLA_MAJOR_VERSION 0)
set(MCNLA_MINOR_VERSION 6)
set(MCNLA_PATCH_VERSION 0)
set(MCNLA_VERSION "${MCNLA_MAJOR_VERSION}.${MCNLA_MINOR_VERSION}.${MCNLA_PATCH_VERSION}")

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Set the paths
include_directories(${target} "${PROJECT_BINARY_DIR}/include" "${PROJECT_SOURCE_DIR}/include")
list(APPEND DEFS "-DMCNLA_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")

# Include functions
include(cmake/functions.cmake)

# Sets the options
include(cmake/options.cmake)

# Sets the packages
include(cmake/packages.cmake)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(report)
add_subdirectory(check)
add_subdirectory(doxygen)

# Create configure files
include(cmake/configure.cmake)

# Display message
include(cmake/display.cmake)
