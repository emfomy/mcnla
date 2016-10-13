# Set options
option(MCNLA_USE_MKL    "Uses MKL as BLAS and LAPACK." "OFF")
option(MCNLA_BUILD_DEMO "Build demo codes."            "ON")
option(MCNLA_BUILD_TEST "Build test codes."            "ON")
option(MCNLA_BUILD_DOC  "Build documentation."         "ON")

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
