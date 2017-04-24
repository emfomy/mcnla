# report/report.cmake

macro(_ADD_REPORT_PREDO)
  set(reporttarget mcnla_report_${reportname})
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/src/${reporttype}/${reportname}.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/${reporttype}/${reportname}/*.cpp")

  if(MCNLA_INSTALL_DEMO)
    add_executable(${reporttarget} ${files})
  else()
    add_executable(${reporttarget} EXCLUDE_FROM_ALL ${files})
  endif()

  set_target_properties(${reporttarget} PROPERTIES SUFFIX "${BIN_SUFFIX}")
  target_include_directories(${reporttarget} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${reporttarget} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${reporttarget} PUBLIC SYSTEM ${INCS})
  target_link_libraries(${reporttarget} ${LIBS})
  target_compile_definitions(${reporttarget} PUBLIC ${DEFS} ${ARGN})
  set_target_properties(${reporttarget} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${reporttarget} PROPERTIES LINK_FLAGS    ${LNKFLGS})
  set(CMAKE_REPORT_TARGETS ${CMAKE_REPORT_TARGETS} ${reporttarget} PARENT_SCOPE)

  if(MCNLA_INSTALL_DEMO)
    install(TARGETS ${reporttarget} RUNTIME DESTINATION ${BIN_FOLDER}/report)
  endif()
endmacro()

################################################################################

macro(_ADD_REPORT)
  _add_report_predo()

  # Add rule
  add_custom_target(
    run_report_${reportname}
    COMMAND bash script/${reporttype}.sh ./${reporttarget}${BIN_SUFFIX}
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
