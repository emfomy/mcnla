# Break
if(NOT MCNLA_BUILD_DEMO AND NOT MCNLA_BUILD_TEST)
  return()
endif()

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -g -Wall -Wextra -Wpedantic")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic")

# MKL
if(MCNLA_USE_MKL)
  find_package(MKL REQUIRED)
  if(MKL_FOUND)
    list(APPEND INCS "${MKL_INCLUDES}")
    list(APPEND LIBS "${MKL_LIBRARIES}")
    set(COMFLGS "${COMFLGS} ${MKL_FLAGS}")
  endif()
endif()

# LAPACK
if(NOT MCNLA_USE_MKL)
  find_package(LAPACK REQUIRED)
  if(LAPACK_FOUND)
    list(APPEND LIBS "${LAPACK_LIBRARIES}")
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
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes.")
