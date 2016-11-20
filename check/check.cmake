# check/check.cmake

macro(_ADD_CHECK_PREDO checktype)
  # Set target name
  get_filename_component(checkname ${checkpath} NAME)
  if(NOT ${checktype} STREQUAL "")
    set(checkname ${checkname}_${checktype})
  endif()
  set(checktarget mcnla_test_${checkname})

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${checkpath}/${checktype}/*.cpp")
  list(SORT files)
  list(REVERSE files)
  add_executable(${checktarget} EXCLUDE_FROM_ALL ${checkmain} ${files})
  target_include_directories(${checktarget} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${checktarget} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${checktarget} SYSTEM PUBLIC ${INCS})
  target_link_libraries(${checktarget} ${LIBS})
  target_compile_definitions(${checktarget} PUBLIC ${DEFS})
  target_compile_definitions(${checktarget} PUBLIC ${defs})
  target_compile_definitions(${checktarget} PUBLIC "MCNLA_CHECK_NAME=\"${checkcomment}\"")
  set_target_properties(${checktarget} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${checktarget} PROPERTIES LINK_FLAGS    ${LNKFLGS})
  set(CMAKE_CHECK_TARGETS ${CMAKE_CHECK_TARGETS} ${checktarget} PARENT_SCOPE)
  list(REVERSE files)
endmacro()

################################################################################

macro(_ADD_CHECK checktype)
  set(checkmain check.cpp)
  _add_check_predo("${checktype}" "")
  gtest_add_tests(${checktarget} "" ${checkmain} ${files})

  # Add rule
  add_custom_target(
    run_${checkname}
    COMMAND ./${checktarget}
    DEPENDS ${checktarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Check test ${checkpath}"
  )
  set(CMAKE_CHECK_RULES ${CMAKE_CHECK_RULES} run_${checkname} PARENT_SCOPE)
endmacro()

macro(_ADD_MPI_CHECK checktype)
  if(NOT ARGN)
      message(FATAL_ERROR "Missing ARGN for _ADD_MPI_CHECK")
  endif()

  set(checkmain check_mpi.cpp)
  _add_check_predo("${checktype}")

  foreach(procs ${ARGN})
    add_test(NAME ${checkname0}_${procs} COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${procs} ${checktarget})

    # Add rule
    add_custom_target(
      run_${checkname}_${procs}
      COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${procs} ${checktarget}
      DEPENDS ${checktarget}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Check test ${checkpath}"
    )
    set(CMAKE_CHECK_RULES ${CMAKE_CHECK_RULES} run_${checkname0}_${procs} PARENT_SCOPE)
  endforeach()
endmacro()

################################################################################

function(ADD_CHECK checkpath checkcomment)
  list(APPEND DEFS "MCNLA_USE_GTEST")
  _add_check("")
endfunction()

function(ADD_CHECK_TEST checkpath checkcomment)
  list(APPEND DEFS "MCNLA_USE_GTEST")
  _add_check("test")
endfunction()

function(ADD_CHECK_DEATH checkpath checkcomment)
  list(REMOVE_ITEM DEFS "MCNLA_USE_GTEST")
  _add_check("death_test")
endfunction()

################################################################################

function(ADD_MPI_CHECK checkpath checkcomment checkname0)
  list(APPEND DEFS "MCNLA_USE_GTEST")
  _add_mpi_check("" ${ARGN})
endfunction()
