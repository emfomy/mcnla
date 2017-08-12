# report/report.cmake

macro(_ADD_REPORT_PREDO)
  set(reporttarget mcnla_report_${reportname})
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/src/${reporttype}/${reportname}.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/${reporttype}/${reportname}/*.cpp")

  if(MCNLA_INSTALL_DEMO)
    add_executable(${reporttarget} ${files})
    install(TARGETS ${reporttarget} RUNTIME DESTINATION ${BIN_FOLDER}/report)
  else()
    add_executable(${reporttarget} EXCLUDE_FROM_ALL ${files})
  endif()

  mcnla_set_target(${reporttarget})

  set(CMAKE_REPORT_TARGETS ${CMAKE_REPORT_TARGETS} ${reporttarget} PARENT_SCOPE)
endmacro()

################################################################################

macro(_ADD_REPORT)
  _add_report_predo()

  # Add rule
  add_custom_target(
    run_report_${reportname}
    COMMAND bash ${CMAKE_CURRENT_BINARY_DIR}/script/${reporttype}.sh $<TARGET_FILE:${reporttarget}>
    DEPENDS ${reporttarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Run report ${reportname}"
  )
  set(CMAKE_REPORT_RULES ${CMAKE_REPORT_RULES} run_report_${reportname} PARENT_SCOPE)
endmacro()

################################################################################

function(ADD_REPORT reporttype reportname)
  _add_report()
endfunction()
