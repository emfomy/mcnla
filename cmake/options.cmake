# Set options
option(MCNLA_USE_MKL    "Uses MKL as BLAS and LAPACK." "OFF")
option(MCNLA_USE_ILP64  "Uses 64bit integer."          "OFF")
option(MCNLA_BUILD_DEMO "Build demo codes."            "ON")
option(MCNLA_BUILD_TEST "Build test codes."            "ON")
option(MCNLA_BUILD_DOC  "Build documentation."         "ON")

# Set variables
unset(MKL_USE_ILP64)
if(MCNLA_USE_MKL)
  list(APPEND DEFS "MCNLA_USE_MKL")
  set(MKL_USE_ILP64 ${MCNLA_USE_ILP64})
endif()
if(NOT MCNLA_USE_ILP64)
  set(MCNLA_SYSTEM_INT_SIZE "32")
else()
  set(MCNLA_SYSTEM_INT_SIZE "64")
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
