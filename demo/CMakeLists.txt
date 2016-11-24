# The CMake setting of 'demo/'

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

# Set target
add_executable(demo EXCLUDE_FROM_ALL test.cpp)
target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}/include")
target_include_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(demo PUBLIC SYSTEM ${INCS})
target_link_libraries(demo ${LIBS})
target_compile_definitions(demo PUBLIC ${DEFS})
set_target_properties(demo PROPERTIES COMPILE_FLAGS ${COMFLGS})
set_target_properties(demo PROPERTIES LINK_FLAGS    ${LNKFLGS})

# Add rule 'run'
add_custom_target(
  run
  COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./demo
  DEPENDS demo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running demo"
)
