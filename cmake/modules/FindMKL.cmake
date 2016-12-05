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
set(INTEL_ROOT "/opt/intel" CACHE PATH "The root path of Intel Parallel Studio.")

unset(MKL_FLAG CACHE)
unset(MKL_INCLUDE CACHE)
unset(MKL_LIBRARY_CORE CACHE)
unset(MKL_LIBRARY_THREAD CACHE)
unset(MKL_LIBRARY_LP CACHE)

################################################################################

if(NOT MKL_ILP64)
  set(mkllib  "mkl_intel_lp64")
  set(mklflag "-m64")
else()
  set(mkllib  "mkl_intel_ilp64")
  set(mklflag "-DMKL_ILP64 -m64")
endif()

################################################################################

set(MKL_FLAG "${mklflag}" CACHE PATH "The compiler flag of Intel MKL." FORCE)

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

if(MKL_OMP STREQUAL "GOMP")
  find_library(
    MKL_LIBRARY_GNU_THREAD
    NAMES mkl_gnu_thread
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The GNU thread library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_GNU_THREAD})
  set(GOMP_LIBRARY "-lgomp" CACHE STRING "The GNU thread library." FORCE)
  set(OMP_LIBRARY ${GOMP_LIBRARY})
elseif(MKL_OMP STREQUAL "IOMP")
  find_library(
    MKL_LIBRARY_INTEL_THREAD
    NAMES mkl_intel_thread
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The Intel thread library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_INTEL_THREAD})
  find_library(
    IOMP_LIBRARY
    NAMES iomp5
    HINTS "${INTEL_ROOT}/lib/intel64"
    DOC "The Intel thread library."
  )
  set(OMP_LIBRARY ${IOMP_LIBRARY})
else()
  find_library(
    MKL_LIBRARY_SEQUENTIAL
    NAMES mkl_sequential
    HINTS "${MKL_ROOT}/lib/intel64"
    DOC "The sequential library of Intel MKL."
  )
  set(MKL_LIBRARY_THREAD ${MKL_LIBRARY_SEQUENTIAL})
  unset(OMP_LIBRARY)
endif()

find_library(
  MKL_LIBRARY_LP
  NAMES ${mkllib}
  HINTS "${MKL_ROOT}/lib/intel64"
  DOC "The integer library of Intel MKL."
)

################################################################################

include(FindPackageHandleStandardArgs)
set(MKL_LIBS "${MKL_LIBRARY_LP};${MKL_LIBRARY_THREAD};${MKL_LIBRARY_CORE}")
if(MKL_OMP)
  find_package_handle_standard_args(
    MKL DEFAULT_MSG MKL_LIBS MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP OMP_LIBRARY MKL_INCLUDE MKL_FLAG
  )
else()
  find_package_handle_standard_args(
    MKL DEFAULT_MSG MKL_LIBS MKL_LIBRARY_CORE MKL_LIBRARY_THREAD MKL_LIBRARY_LP MKL_INCLUDE MKL_FLAG
  )
endif()

mark_as_advanced(MKL_LIBRARY_CORE MKL_LIBRARY_GNU_THREAD MKL_LIBRARY_INTEL_THREAD MKL_LIBRARY_SEQUENTIAL MKL_LIBRARY_LP GOMP_LIBRARY IOMP_LIBRARY MKL_INCLUDE MKL_FLAG)

set(MKL_INCLUDES  "${MKL_INCLUDE}")
set(MKL_LIBRARIES "-Wl,--start-group ${MKL_LIBRARY_CORE} ${MKL_LIBRARY_THREAD} ${MKL_LIBRARY_LP} -Wl,--end-group ${OMP_LIBRARY} -lpthread -lm -ldl")
set(MKL_FLAGS     "${MKL_FLAG}")
