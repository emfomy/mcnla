#.rst:
# FindMKL
# ---------
#
# Locate the Intel Math Kernel Library.
#

if(NOT DEFINED MKLROOT OR MKLROOT STREQUAL "")
  set(MKLROOT "$ENV{MKLROOT}")
endif()

set(MKLROOT "${MKLROOT}" CACHE PATH "The root path of Intel MKL." FORCE)

################################################################################

if(NOT MKL_ILP64)
  set(mkllib "mkl_intel_lp64")
  set(mklflg "-m64")
else()
  set(mkllib "mkl_intel_ilp64")
  set(mklflg "-DMKL_ILP64 -m64")
endif()

################################################################################

set(MKL_FLAG "${mklflg}" CACHE PATH "The compiler flag of Intel MKL." FORCE)

################################################################################

find_path(
  MKL_INCLUDE mkl.h
  HINTS "${MKLROOT}/include"
  DOC "The include directory of Intel MKL."
)

################################################################################

find_library(
  MKL_LIBRARY_CORE
  NAMES mkl_core
  HINTS "${MKLROOT}/lib/intel64"
  DOC "The core library of Intel MKL."
)

find_library(
  MKL_LIBRARY_THREAD
  NAMES mkl_gnu_thread
  HINTS "${MKLROOT}/lib/intel64"
  DOC "The thread library of Intel MKL."
)

find_library(
  MKL_LIBRARY_LP
  NAMES ${mkllib}
  HINTS "${MKLROOT}/lib/intel64"
  DOC "The integer library of Intel MKL."
)

################################################################################

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  MKL DEFAULT_MSG MKLROOT MKL_FLAG MKL_INCLUDE MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP
)

mark_as_advanced(MKL_FLAG MKL_INCLUDE MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP)

set(MKL_INCLUDES  "${MKL_INCLUDE}")
set(MKL_LIBRARIES "-Wl,--start-group ${MKL_LIBRARY_CORE} ${MKL_LIBRARY_THREAD} ${MKL_LIBRARY_LP} -Wl,--end-group -lgomp -lpthread -lm -ldl")
set(MKL_FLAGS     "${MKL_FLAG}")
