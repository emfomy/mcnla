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
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set word size
set(MCNLA_SYSTEM_INT_SIZE 32 CACHE PATH "The system integer size.")
if(MCNLA_SYSTEM_INT_SIZE EQUAL 32)
  message(STATUS "Uses 32bit integer (LP64).")
elseif(MCNLA_SYSTEM_INT_SIZE EQUAL 64)
  message(STATUS "Uses 64bit integer (ILP64).")
else()
  message(SEND_ERROR "Unsupport system integer size! (Only support 32 or 64.)")
endif()

# Add subdirectories
add_subdirectory(cmake)
add_subdirectory(include)
add_subdirectory(doxygen)
if(NOT CMAKE_BUILD_TYPE STREQUAL "Doc")
  add_subdirectory(demo)
endif()

# Display message
message(STATUS "================================================================")
message(STATUS "Set 'MCNLA_SYSTEM_INT_SIZE' to change the system integer size: 32(LP64) / 64(ILP64).")
message(STATUS "Set 'MCNLA_USE_MKL' to enable Intel MKL.")
message(STATUS "Set 'MPI_PROCS' to set the number of MPI processes.")
message(STATUS "Set 'CMAKE_BUILD_TYPE=Doc' for creating documentation only.")
message(STATUS "================================================================")
