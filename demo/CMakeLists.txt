# The CMake setting of 'demo/'

macro(SET_TARGET target files)
  # Set target
  add_executable(${target} EXCLUDE_FROM_ALL ${files})
  target_include_directories(${target} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${target} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${target} PUBLIC SYSTEM ${INCS})
  target_link_libraries(${target} ${LIBS})
  target_compile_definitions(${target} PUBLIC ${DEFS})
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./${target}
    DEPENDS ${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )
endmacro()

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

# Set target (demo)
set_target(demo demo.cpp)

# Set target (plain)
set_target(plain isvd_plain.cpp)

# Add rule 'run'
add_custom_target(run DEPENDS run_demo)
