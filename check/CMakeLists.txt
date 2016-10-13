# The CMake setting of 'check/'

# Break
if(NOT MCNLA_BUILD_TEST)
  return()
endif()

# GTEST
set(GTEST_ROOT "" CACHE PATH "The root path of Google Test.")
if(${CMAKE_VERSION} VERSION_LESS 3.1)
  find_package(GTest_ REQUIRED)
else()
  find_package(GTest REQUIRED)
endif()
if(GTEST_FOUND)
  set(INCS ${INCS} "${GTEST_INCLUDE_DIRS}")
  set(LIBS ${LIBS} "${GTEST_BOTH_LIBRARIES}")
endif()

# Add check folders
include(check.cmake)
add_check(core/matrix/dense "Dense Container Module test")

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
