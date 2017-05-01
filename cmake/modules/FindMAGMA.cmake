#.rst:
# FindMAGMA
# ---------
#
# Locate the MAGMA Library.
#

################################################################################

if(NOT MAGMA_ROOT AND NOT $ENV{MAGMA_ROOT} STREQUAL "")
  set(MAGMA_ROOT "$ENV{MAGMA_ROOT}")
endif()

################################################################################

find_path(
  MAGMA_INCLUDE magma.h
  HINTS "${MAGMA_ROOT}/include"
  DOC "The include directory of MAGMA."
)

find_library(
  MAGMA_LIBRARY
  NAMES magma
  HINTS "${MAGMA_ROOT}/lib"
  DOC "The library of MAGMA."
)

################################################################################

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  MAGMA DEFAULT_MSG MAGMA_LIBRARY MAGMA_INCLUDE
)

mark_as_advanced(MAGMA_LIBRARY MAGMA_INCLUDE)

################################################################################

set(MAGMA_INCLUDES  "${MAGMA_INCLUDE}")
set(MAGMA_LIBRARIES "${MAGMA_LIBRARY}")
if(MAGMA_ROOT STREQUAL "" AND DEFINED MAGMA_INCLUDE)
  get_filename_component(MAGMA_ROOT "${MAGMA_INCLUDE}/.." REALPATH)
endif()

set(MAGMA_ROOT "${MAGMA_ROOT}" CACHE PATH "The root path of MAGMA." FORCE)
