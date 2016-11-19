#.rst:
# FindMKL
# ---------
#
# Locate the Intel Math Kernel Library.
#

set(MKL_ROOT "${MKL_ROOT}")
if(MKL_ROOT STREQUAL "")
  if(DEFINED ENV{MKLROOT})
    set(MKL_ROOT "$ENV{MKLROOT}")
  endif()
endif()

set(MKL_ROOT "${MKL_ROOT}" CACHE PATH "The root path of Intel MKL." FORCE)

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
  HINTS "${MKL_ROOT}/include"
  DOC "The include directory of Intel MKL."
)

################################################################################

find_library(
  MKL_LIBRARY_CORE
  NAMES mkl_core
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The core library of Intel MKL."
)

find_library(
  MKL_LIBRARY_THREAD
  NAMES mkl_gnu_thread
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The thread library of Intel MKL."
)

find_library(
  MKL_LIBRARY_LP
  NAMES ${mkllib}
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The integer library of Intel MKL."
)

################################################################################

include(FindPackageHandleStandardArgs)
set(MKL_LIBS "${MKL_LIBRARY_CORE};${MKL_LIBRARY_THREAD};${MKL_LIBRARY_LP}")
find_package_handle_standard_args(
  MKL DEFAULT_MSG MKL_LIBS MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG
)

mark_as_advanced(MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG)

set(MKL_INCLUDES  "${MKL_INCLUDE}")
set(MKL_LIBRARIES "-Wl,--start-group ${MKL_LIBRARY_CORE} ${MKL_LIBRARY_THREAD} ${MKL_LIBRARY_LP} -Wl,--end-group -lgomp -lpthread -lm -ldl")
set(MKL_FLAGS     "${MKL_FLAG}")
