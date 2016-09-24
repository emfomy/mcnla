# The CMake setting of 'demo/'

# Set target
add_executable(demo demo.cpp)
include_directories("${PROJECT_BINARY_DIR}/include" "${PROJECT_SOURCE_DIR}/include")
include_directories(SYSTEM ${INCS})
target_link_libraries(demo ${LIBS})
set_target_properties(demo PROPERTIES COMPILE_DEFINITIONS ${DEFS})
set_target_properties(demo PROPERTIES COMPILE_FLAGS       ${COMFLGS})
set_target_properties(demo PROPERTIES LINK_FLAGS          ${LNKFLGS})

# Add rule 'run'
add_custom_target(
  run
  COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./demo
  DEPENDS demo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running demo"
)
