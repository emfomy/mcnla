# The CMake setting of 'demo/'

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set target
  if(MCNLA_INSTALL_DEMO)
    add_executable(mcnla_${target} ${files})
    install(TARGETS mcnla_${target} RUNTIME DESTINATION ${BIN_FOLDER}/demo)
  else()
    add_executable(mcnla_${target} EXCLUDE_FROM_ALL ${files})
  endif()

  mcnla_set_target(mcnla_${target})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} $<TARGET_FILE:mcnla_${target}>
    DEPENDS mcnla_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )
endmacro()

# Set target (demo)
set_target(demo demo.cpp)

# Set target (demo_plain)
# set_target(demo_plain demo_plain.cpp)

# Set target (test)
set_target(test test.cpp)
