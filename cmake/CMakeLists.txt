# The CMake setting of 'demo/'

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -Wpedantic" PARENT_SCOPE)
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic" PARENT_SCOPE)

# MKL
set(ISVD_USE_MKL false CACHE PATH "Uses MKL as BLAS and LAPACK.")
if(ISVD_USE_MKL)
  set(DEFS ${DEFS} "-DISVD_USE_MKL")

  if(NOT DEFINED MKLROOT)
    set(MKLROOT "$ENV{MKLROOT}")
  endif()
  set(MKLROOT ${MKLROOT} CACHE PATH "The root path of Intel MKL")

  if(DEFINED MKLROOT)
    set(MKL_FOUND true)
  else()
    message(SEND_ERROR "Intel MKL is not found (missing:  MKLROOT)")
  endif()

  if(MKL_FOUND)
    message(STATUS "Found Intel MKL")
    set(INCS ${INCS} "${MKLROOT}/include")

    if(ISVD_SYSTEM_INT_SIZE EQUAL 32)
      set(LIBS ${LIBS} "-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a -Wl,--end-group -liomp5 -lpthread -lm -ldl")
      set(COMFLGS "${COMFLGS} -m64")
    elseif(ISVD_SYSTEM_INT_SIZE EQUAL 64)
      set(LIBS ${LIBS} "-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a -Wl,--end-group -liomp5 -lpthread -lm -ldl")
      set(COMFLGS "${COMFLGS} -DMKL_ILP64 -m64")
    endif()
  endif()
endif()

# MPI
find_package(MPI REQUIRED)
if(MPI_FOUND)
  set(INCS ${INCS} "${MPI_INCLUDE_PATH}")
  set(LIBS ${LIBS} "${MPI_LIBRARIES}")
  set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}")
  set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}")
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes")

# Boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
  set(INCS ${INCS} "${Boost_INCLUDE_DIRS}")
  set(LIBS ${LIBS} "${Boost_LIBRARIES}")
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes")

# LAPACK
if(NOT ISVD_USE_MKL)
  find_package(LAPACK REQUIRED)
  if(LAPACK_FOUND)
    set(LIBS ${LIBS} "${LAPACK_LIBRARIES}")
  endif()
endif()

set(INCS    "${INCS}"    PARENT_SCOPE)
set(LIBS    "${LIBS}"    PARENT_SCOPE)
set(DEFS    "${DEFS}"    PARENT_SCOPE)
set(COMFLGS "${COMFLGS}" PARENT_SCOPE)
set(LNKFLGS "${LNKFLGS}" PARENT_SCOPE)
