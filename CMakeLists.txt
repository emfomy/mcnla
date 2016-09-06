# The main CMake setting

# Set project
project(iSVD)
cmake_minimum_required(VERSION 2.8)

# Set version number
set(ISVD_VERSION_MAJOR 0)
set(ISVD_VERSION_MINOR 2)
set(ISVD_VERSION_PATCH 0)

# Set Makefile
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set word size
set(ISVD_SYSTEM_INT_SIZE 32 CACHE PATH "The system integer size.")
if(ISVD_SYSTEM_INT_SIZE EQUAL 32)
  message(STATUS "Uses 32bit integer (LP64).")
elseif(ISVD_SYSTEM_INT_SIZE EQUAL 64)
  message(STATUS "Uses 64bit integer (ILP64).")
else()
  message(SEND_ERROR "Unsupport system integer size! (Only support 32 or 64.)")
endif()

# Add subdirectories
add_subdirectory(cmake)
add_subdirectory(include)
add_subdirectory(doxygen)
add_subdirectory(demo)

# Display message
message(STATUS "================================================================")
message(STATUS "Set 'ISVD_SYSTEM_INT_SIZE' to change the system integer size: 32(LP64) / 64(ILP64).")
message(STATUS "Set 'ISVD_USE_MKL' to enable Intel MKL.")
message(STATUS "Set 'MPI_PROCS' to set the number of MPI processes.")
message(STATUS "================================================================")
