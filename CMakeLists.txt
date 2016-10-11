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

# Set options
option(MCNLA_USE_MKL        "Uses MKL as BLAS and LAPACK." "OFF")
option(MCNLA_BUILD_DEMO     "Build demo codes."            "ON")
option(MCNLA_BUILD_TEST     "Build test codes."            "ON")
option(MCNLA_BUILD_DOC      "Build documentation."         "ON")

# Set word size
set(MCNLA_SYSTEM_INT_SIZE 32 CACHE PATH "The system integer size.")
if(MCNLA_SYSTEM_INT_SIZE EQUAL 32)
  message(STATUS "Uses 32bit integer (LP64).")
elseif(MCNLA_SYSTEM_INT_SIZE EQUAL 64)
  message(STATUS "Uses 64bit integer (ILP64).")
else()
  message(SEND_ERROR "Unsupport system integer size! (Only support 32 or 64.)")
endif()

# Check compiler support
if(MCNLA_BUILD_DEMO OR MCNLA_BUILD_TEST)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  if(NOT COMPILER_SUPPORTS_CXX11)
    message(
      FATAL_ERROR
      "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. "
      "Please use a diffferent C++ compiler."
    )
  endif()
endif()

# Enable testing
if(MCNLA_BUILD_TEST)
  enable_testing()
endif()

# Add subdirectories
add_subdirectory(cmake)
add_subdirectory(doxygen)
add_subdirectory(demo)
add_subdirectory(check)

# Create configure files
file(
  GLOB_RECURSE configfiles
  RELATIVE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*.in"
)
foreach(configfile ${configfiles})
  string(REGEX REPLACE "\\.[^.]*$" "" file ${configfile})
  configure_file(
    "${PROJECT_SOURCE_DIR}/${configfile}"
    "${PROJECT_BINARY_DIR}/${file}"
  )
endforeach()

# Display message
message(STATUS "================================================================")
message(STATUS "Set 'MCNLA_SYSTEM_INT_SIZE' to change the system integer size: 32(LP64) / 64(ILP64).")
message(STATUS "Set 'MCNLA_USE_MKL' to enable Intel MKL.")
message(STATUS "Set 'MPI_PROCS' to set the number of MPI processes.")
message(STATUS "Set 'CMAKE_BUILD_TYPE=Doc' for creating documentation only.")
message(STATUS "================================================================")
