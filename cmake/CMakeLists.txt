# The CMake setting of 'demo/'

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -Wpedantic" PARENT_SCOPE)
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic" PARENT_SCOPE)

# MKL
set(ISVD_USE_MKL false CACHE PATH "Uses MKL as BLAS and LAPACK.")
if(ISVD_USE_MKL)
  set(DEFS ${DEFS} "-DISVD_USE_MKL")
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
find_package(LAPACK REQUIRED)
if(LAPACK_FOUND)
  set(LIBS ${LIBS} "${LAPACK_LIBRARIES}")
endif()

set(INCS    "${INCS}"    PARENT_SCOPE)
set(LIBS    "${LIBS}"    PARENT_SCOPE)
set(DEFS    "${DEFS}"    PARENT_SCOPE)
set(COMFLGS "${COMFLGS}" PARENT_SCOPE)
set(LNKFLGS "${LNKFLGS}" PARENT_SCOPE)
