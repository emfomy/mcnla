# The CMake setting of 'demo/'

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -Wpedantic")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic")

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

# Set target
add_executable(demo test.cpp)
include_directories("${PROJECT_BINARY_DIR}/include" "${PROJECT_SOURCE_DIR}/include")
include_directories(SYSTEM ${INCS})
target_link_libraries(demo ${LIBS})
set_target_properties(demo PROPERTIES COMPILE_FLAGS ${COMFLGS})
set_target_properties(demo PROPERTIES LINK_FLAGS    ${LNKFLGS})

# Add rule 'run'
add_custom_target(
  run
  COMMAND ./demo
  DEPENDS demo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running demo"
)
