# The CMake setting of 'demo/'

# Set complier flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall -Wextra -Wpedantic")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -Wpedantic")

# MPI
find_package(MPI REQUIRED)

if(MPI_FOUND)
  message(STATUS "Found MPI")
  set(INCS ${INCS} "${MPI_INCLUDE_PATH}")
  set(LIBS ${LIBS} "${MPI_LIBRARIES}")
  set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}")
  set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}")
endif()
set(MPI_PROCS 4 CACHE PATH "The number of MPI processes")

# MKL
if(NOT DEFINED MKLROOT)
  set(MKLROOT "$ENV{MKLROOT}")
endif()
set(MKLROOT ${MKLROOT} CACHE PATH "The root path of Intel MKL")

if(DEFINED MKLROOT)
  set(MKL_FOUND true)
else()
  message(STATUS "Intel MKL is not found (missing:  MKLROOT)")
endif()

if(MKL_FOUND)
  message(STATUS "Found Intel MKL")
  set(INCS ${INCS} "${MKLROOT}/include")
  set(LIBS ${LIBS} "-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a -Wl,--end-group -liomp5 -lpthread -lm -ldl")
  set(COMFLGS "${COMFLGS} -m64")
endif()

# # Set target
# add_executable(demo demo.cpp)
# include_directories("${PROJECT_BINARY_DIR}/include" "${PROJECT_SOURCE_DIR}/include")
# include_directories(SYSTEM ${INCS})
# target_link_libraries(demo ${LIBS})
# set_target_properties(demo PROPERTIES COMPILE_FLAGS ${COMFLGS})
# set_target_properties(demo PROPERTIES LINK_FLAGS    ${LNKFLGS})

# # Add rule 'run'
# add_custom_target(
#   run
#   COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./demo
#   DEPENDS demo
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#   COMMENT "Running demo"
# )

# Set target
add_executable(test test.cpp)
include_directories("${PROJECT_BINARY_DIR}/include" "${PROJECT_SOURCE_DIR}/include")
include_directories(SYSTEM ${INCS})
target_link_libraries(test ${LIBS})
set_target_properties(test PROPERTIES COMPILE_FLAGS ${COMFLGS})
set_target_properties(test PROPERTIES LINK_FLAGS    ${LNKFLGS})

# Add rule 'run'
add_custom_target(
  run
  COMMAND ./test
  DEPENDS test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running test"
)
