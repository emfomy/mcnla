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
  else()
    add_executable(mcnla_${target} EXCLUDE_FROM_ALL ${files})
  endif()
  target_include_directories(mcnla_${target} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(mcnla_${target} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(mcnla_${target} PUBLIC SYSTEM ${INCS})
  target_link_libraries(mcnla_${target} ${LIBS})
  target_compile_definitions(mcnla_${target} PUBLIC ${DEFS} ${ARGN})
  set_target_properties(mcnla_${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(mcnla_${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./mcnla_${target}
    DEPENDS mcnla_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )

  if(MCNLA_INSTALL_DEMO)
    install(TARGETS mcnla_${target} RUNTIME DESTINATION bin/demo)
  endif()
endmacro()

# Set target (demo1)
set_target(demo1 demo1.cpp)

# Set target (demo2)
set_target(demo2 demo2.cpp)

# Set target (demo_plain)
set_target(demo_plain demo_plain.cpp)

# Set target (demo_kn)
set_target(demo_kn demo_kn.cpp)

# Set target (test)
set_target(test test.cpp)

# Add rule 'run'
add_custom_target(run DEPENDS run_test)
