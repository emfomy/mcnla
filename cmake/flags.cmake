# Set options
if(MCNLA_USE_MKL)
  list(APPEND DEFS "MCNLA_USE_MKL")
endif()

# Break
if(NOT MCNLA_BUILD_DEMO AND NOT MCNLA_BUILD_TEST)
  return()
endif()

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -g -Wall -Wextra -Wpedantic")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic")

# MKL
if(MCNLA_USE_MKL)
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
    list(APPEND INCS "${MKLROOT}/include")

    if(MCNLA_SYSTEM_INT_SIZE EQUAL 32)
      list(APPEND LIBS "-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl")
      set(COMFLGS "${COMFLGS} -m64")
    elseif(MCNLA_SYSTEM_INT_SIZE EQUAL 64)
      list(APPEND LIBS "-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl")
      set(COMFLGS "${COMFLGS} -DMKL_ILP64 -m64")
    endif()
  endif()
endif()

# MPI
find_package(MPI REQUIRED)
if(MPI_FOUND)
  list(APPEND INCS "${MPI_INCLUDE_PATH}")
  list(APPEND LIBS "${MPI_LIBRARIES}")
  set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}")
  set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}")
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes")

# LAPACK
if(NOT MCNLA_USE_MKL)
  find_package(LAPACK REQUIRED)
  if(LAPACK_FOUND)
    list(APPEND LIBS "${LAPACK_LIBRARIES}")
  endif()
endif()
