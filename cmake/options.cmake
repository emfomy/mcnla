# Set install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/opt/mcnla-${MCNLA_MAJOR_VERSION}.${MCNLA_MINOR_VERSION}" CACHE PATH "The install path prefix." FORCE)
endif()

# Set options
option(MCNLA_BUILD_DRIVER  "Build driver codes."   "ON")
option(MCNLA_BUILD_DEMO    "Build demo codes."     "ON")
option(MCNLA_BUILD_REPOET  "Build report codes."   "ON")
option(MCNLA_BUILD_TEST    "Build test codes."     "OFF")
option(MCNLA_BUILD_DOC     "Build documentation."  "OFF")
option(MCNLA_INSTALL_DEMO  "Install demos."        "OFF")

set(MCNLA_INT_SIZE "32" CACHE STRING "System integer size. [32/64]")
set_property(CACHE MCNLA_INT_SIZE PROPERTY STRINGS "32;64")
if(NOT MCNLA_INT_SIZE STREQUAL "32" AND NOT MCNLA_INT_SIZE STREQUAL "64" )
  message(FATAL_ERROR "MCNLA_INT_SIZE must be either 32 or 64")
endif()

set(MCNLA_BLAS "BLAS" CACHE STRING "Selected BLAS/LAPACK library. [BLAS/MKL]")
set_property(CACHE MCNLA_BLAS PROPERTY STRINGS "BLAS;MKL")
if(NOT MCNLA_BLAS STREQUAL "BLAS" AND NOT MCNLA_BLAS STREQUAL "MKL" )
  message(FATAL_ERROR "BLAS must be either BLAS or MKL")
endif()

set(MCNLA_OMP "OFF" CACHE STRING "Selected OpenMP library. [OFF/GOMP/IOMP] (Require 'MCNLA_BLAS = MKL')")
set_property(CACHE MCNLA_OMP PROPERTY STRINGS "OFF;GOMP;IOMP")
if(NOT MCNLA_OMP STREQUAL "OFF" AND NOT MCNLA_OMP STREQUAL "GOMP" AND NOT MCNLA_OMP STREQUAL "IOMP" )
  message(FATAL_ERROR "MCNLA_OMP must be either OFF, GOMP, or IOMP")
endif()

# option(MCNLA_USE_GPU       "Enable GPU support."   "OFF")

set(MPI_PROCS 4 CACHE STRING "The number of MPI processes used in demo codes.")

# Set variables
if(MCNLA_BUILD_DRIVER OR MCNLA_BUILD_DEMO OR MCNLA_BUILD_REPOET OR MCNLA_BUILD_TEST)
  set(MCNLA_BUILD_BIN "ON")
endif()

if(MCNLA_INT_SIZE STREQUAL "32")
  set(BIN_SUFFIX "")
  set(BIN_FOLDER "bin")
  set(MCNLA_USE_ILP64 "OFF")
else()
  set(BIN_SUFFIX "_64")
  set(BIN_FOLDER "bin64")
  set(MCNLA_USE_ILP64 "ON")
  list(APPEND DEFS "MCNLA_USE_ILP64")
endif()

if(MCNLA_BLAS STREQUAL "MKL")
  list(APPEND DEFS "MCNLA_USE_MKL")
  set(MKL_ILP64 ${MCNLA_USE_ILP64})
  set(MCNLA_USE_MKL "ON")
else()
  unset(MKL_ILP64)
  set(MCNLA_USE_MKL "OFF")
endif()

set(MKL_OMP ${MCNLA_OMP})

# if(MCNLA_USE_GPU)
#   list(APPEND DEFS "MCNLA_USE_GPU")
#   if(MCNLA_USE_ILP64)
#     list(APPEND DEFS "MAGMA_ILP64")
#   endif()
# endif()

# Enable testing
if(MCNLA_BUILD_TEST)
  enable_testing()
endif()
