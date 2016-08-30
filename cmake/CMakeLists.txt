# The CMake setting of 'demo/'

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -Wpedantic" PARENT_SCOPE)
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic" PARENT_SCOPE)

# MPI
find_package(MPI REQUIRED)
if(MPI_FOUND)
  set(INCS ${INCS} "${MPI_INCLUDE_PATH}" PARENT_SCOPE)
  set(LIBS ${LIBS} "${MPI_LIBRARIES}" PARENT_SCOPE)
  set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}" PARENT_SCOPE)
  set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}" PARENT_SCOPE)
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes" PARENT_SCOPE)

# Boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
  set(INCS ${INCS} "${Boost_INCLUDE_DIRS}" PARENT_SCOPE)
  set(LIBS ${LIBS} "${Boost_LIBRARIES}" PARENT_SCOPE)
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes" PARENT_SCOPE)

# LAPACK
find_package(LAPACK REQUIRED)
if(LAPACK_FOUND)
  set(LIBS ${LIBS} "${LAPACK_LIBRARIES}" PARENT_SCOPE)
endif()
