# check/check.cmake

macro(_add_check checkpath checkcomment type)
  # Set target name
  get_filename_component(checkname ${checkpath} NAME)
  if(NOT ${type} STREQUAL "")
    set(checkname "${checkname}_${type}")
  endif()
  set(checktarget "mcnla_test_${checkname}")

  # Set target
  file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${checkpath}/${type}/*.cpp")
  list(SORT files)
  list(REVERSE files)
  add_executable(${checktarget} EXCLUDE_FROM_ALL check.cpp ${files})
  target_include_directories(${checktarget} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${checktarget} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${checktarget} SYSTEM PUBLIC ${INCS})
  target_link_libraries(${checktarget} ${LIBS})
  target_compile_definitions(${checktarget} PUBLIC ${DEFS})
  target_compile_definitions(${checktarget} PUBLIC ${defs})
  target_compile_definitions(${checktarget} PUBLIC "MCNLA_CHECK_NAME=\"${checkcomment}\"")
  set_target_properties(${checktarget} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${checktarget} PROPERTIES LINK_FLAGS    ${LNKFLGS})

  # Add test
  list(REVERSE files)
  # add_test(NAME ${checkpath} COMMAND ${checktarget})
  gtest_add_tests(${checktarget} "" check.cpp ${files})
  set(CMAKE_CHECK_TARGETS ${CMAKE_CHECK_TARGETS} ${checktarget} PARENT_SCOPE)

  # Add rule
  add_custom_target(
    run_${checkname}
    COMMAND ./${checktarget}
    DEPENDS ${checktarget}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Check test ${checkpath}"
  )
  set(CMAKE_CHECK_RULES ${CMAKE_CHECK_RULES} run_${checkname} PARENT_SCOPE)
endmacro(_add_check)

function(add_check checkpath checkcomment)
  list(APPEND DEFS "MCNLA_USE_GTEST")
  _add_check(${checkpath} ${checkcomment})
endfunction(add_check)

function(add_check_test checkpath checkcomment)
  list(APPEND DEFS "MCNLA_USE_GTEST")
  _add_check(${checkpath} ${checkcomment} "test")
endfunction(add_check_test)

function(add_check_death checkpath checkcomment)
  list(REMOVE_ITEM DEFS "MCNLA_USE_GTEST")
  _add_check(${checkpath} ${checkcomment} "death_test")
endfunction(add_check_death)
