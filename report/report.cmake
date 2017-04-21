# report/report.cmake

macro(_ADD_REPORT_PREDO)
  # Set target name
  get_filename_component(reportname ${reportpath} NAME)
  set(reporttarget mcnla_report_${reportname})

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${reportpath}.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/${reportpath}/*.cpp")
  add_executable(${reporttarget} EXCLUDE_FROM_ALL ${files})
  target_include_directories(${reporttarget} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${reporttarget} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${reporttarget} PUBLIC SYSTEM ${INCS})
  target_link_libraries(${reporttarget} ${LIBS})
  target_compile_definitions(${reporttarget} PUBLIC ${DEFS} ${ARGN})
  set_target_properties(${reporttarget} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${reporttarget} PROPERTIES LINK_FLAGS    ${LNKFLGS})
  set(CMAKE_REPORT_TARGETS ${CMAKE_REPORT_TARGETS} ${reporttarget} PARENT_SCOPE)
endmacro()

################################################################################

macro(_ADD_REPORT)
  _add_report_predo()

  # Add rule
  add_custom_target(
    run_report_${reportname}
    COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPI_PROCS} ./${reporttarget}
    DEPENDS ${reporttarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Run report ${reportpath}"
  )
  set(CMAKE_REPORT_RULES ${CMAKE_REPORT_RULES} run_report_${reportname} PARENT_SCOPE)
endmacro()

################################################################################

function(ADD_REPORT reportpath)
  _add_report()
endfunction()
