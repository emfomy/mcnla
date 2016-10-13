# The main CMake setting

# Set project
project(MCNLA)
cmake_minimum_required(VERSION 2.8)
set(MCNLA_NAME "Monte Carlo Numerical Linear Algebra Package")

# Set version number
set(MCNLA_VERSION_MAJOR 0)
set(MCNLA_VERSION_MINOR 3)
set(MCNLA_VERSION_PATCH 0)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

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

# Display message
message(STATUS "================================================================")
message(STATUS "Set 'MCNLA_SYSTEM_INT_SIZE' to change the system integer size: 32(LP64) / 64(ILP64).")
message(STATUS "Set 'MCNLA_USE_MKL' to enable Intel MKL.")
message(STATUS "Set 'MPI_PROCS' to set the number of MPI processes.")
message(STATUS "Set 'CMAKE_BUILD_TYPE=Doc' for creating documentation only.")
message(STATUS "================================================================")
