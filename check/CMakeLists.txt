# The CMake setting of 'check/'

# Break
if(NOT MCNLA_BUILD_TEST)
  return()
endif()

# GTest
if(GTEST_FOUND)
  list(APPEND INCS "${GTEST_INCLUDE_DIRS}")
  list(APPEND LIBS "${GTEST_BOTH_LIBRARIES}")
endif()

# Add check folders
include(check.cmake)

# Add rule 'build_test'
add_custom_target(
  build_test
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Building tests"
)

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Running tests"
)
