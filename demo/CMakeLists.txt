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
  set_target_properties(mcnla_${target} PROPERTIES SUFFIX "${BIN_SUFFIX}")
  target_include_directories(mcnla_${target} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(mcnla_${target} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(mcnla_${target} PUBLIC SYSTEM ${INCS})
  target_link_libraries(mcnla_${target} ${LIBS})
  target_compile_definitions(mcnla_${target} PUBLIC ${DEFS})
  set_target_properties(mcnla_${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(mcnla_${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})

  # Add run rule
  add_custom_target(
    run_${target}
    COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./mcnla_${target}${BIN_SUFFIX}
    DEPENDS mcnla_${target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${target}"
  )

  if(MCNLA_INSTALL_DEMO)
    install(TARGETS mcnla_${target} RUNTIME DESTINATION ${BIN_FOLDER}/demo)
  endif()
endmacro()

# Set target (demo)
set_target(demo demo.cpp)

# Set target (demo_plain)
# set_target(demo_plain demo_plain.cpp)

# # Set target (demo_kn)
# set_target(demo_kn demo_kn.cpp)

# # Set target (demo_kn0)
# set_target(demo_kn0 demo_kn0.cpp)

# Set target (test)
set_target(test test.cpp)
