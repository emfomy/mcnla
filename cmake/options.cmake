# Set install prefix
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/mcnla-${MCNLA_VERSION}" CACHE PATH "The install path prefix." FORCE)
endif()

# Set options
option(MCNLA_BUILD_DRIVER "Build driver codes."                           "ON")
option(MCNLA_BUILD_DEMO   "Build demo codes."                             "ON")
option(MCNLA_BUILD_TEST   "Build test codes."                             "OFF")
option(MCNLA_BUILD_DOC    "Build documentation."                          "OFF")
option(MCNLA_USE_ILP64    "Uses 64bit integer."                           "OFF")
option(MCNLA_USE_MKL      "Uses Intel MKL."                               "OFF")
option(MKL_USE_OMP        "Uses multithread MKL. (Require MCNLA_USE_MKL)" "OFF")
option(MKL_USE_IOMP       "Uses Intel OMP. (Require MKL_USE_OMP)"         "OFF")
option(MCNLA_INSTALL_DEMO "Install demos."                                "OFF")

# Set variables
if(MCNLA_BUILD_DRIVER OR MCNLA_BUILD_DEMO OR MCNLA_BUILD_TEST)
  set(MCNLA_BUILD_BIN "ON")
endif()

if(MCNLA_USE_ILP64)
  list(APPEND DEFS "MCNLA_USE_ILP64")
endif()

if(MCNLA_USE_MKL)
  list(APPEND DEFS "MCNLA_USE_MKL")
  set(MKL_ILP64 ${MCNLA_USE_ILP64})
else()
  unset(MKL_ILP64)
endif()

if(MKL_USE_OMP)
  list(APPEND DEFS "MCNLA_USE_OMP")
  if(MKL_USE_IOMP)
    set(MKL_OMP "IOMP")
  else()
    set(MKL_OMP "GOMP")
  endif()
else()
  set(MKL_OMP "OFF")
endif()

# Check compiler support
if(MCNLA_BUILD_BIN)
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
