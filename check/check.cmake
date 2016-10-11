# check/check.cmake

function(add_check checkname checkcomment)

  # Set target name
  set(checktarget "mcnla_test_${checkname}")

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${checkname}/*.cpp")
  add_executable(${checktarget} EXCLUDE_FROM_ALL check.cpp ${files})
  target_include_directories(${checktarget} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${checktarget} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${checktarget} SYSTEM PUBLIC ${INCS})
  target_link_libraries(${checktarget} ${LIBS})
  target_compile_definitions(${checktarget} PUBLIC ${DEFS})
  target_compile_definitions(${checktarget} PUBLIC "MCNLA_CHECK_NAME=\"${checkcomment}\"")
  set_target_properties(${checktarget} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${checktarget} PROPERTIES LINK_FLAGS    ${LNKFLGS})

  # Add test
  # add_test(NAME ${checkname} COMMAND ${checktarget})
  gtest_add_tests(${checktarget} "" check.cpp)
  set(CMAKE_CHECK_TARGETS ${CMAKE_CHECK_TARGETS} ${checktarget} PARENT_SCOPE)

  # Add rule
  add_custom_target(
    check_${checkname}
    COMMAND ./${checktarget}
    DEPENDS ${checktarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Check test ${checkname}"
  )

endfunction(add_check)
