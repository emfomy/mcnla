# The CMake setting of 'check/'

# Break
if(NOT MCNLA_BUILD_TEST)
  return()
endif()

# GTEST
set(GTEST_ROOT "" CACHE PATH "The root path of Google Test.")
if(${CMAKE_VERSION} VERSION_LESS 3.1)
  find_package(GTest_ 1.8 REQUIRED)
else()
  find_package(GTest  1.8 REQUIRED)
endif()
if(GTEST_FOUND)
  set(INCS ${INCS} "${GTEST_INCLUDE_DIRS}")
  set(LIBS ${LIBS} "${GTEST_BOTH_LIBRARIES}")
endif()

# Add check folders
include(check.cmake)
add_check(core/matrix/dense/dense_vector/test       "Dense Vector test" "MCNLA_USE_GTEST")
add_check(core/matrix/dense/dense_vector/death_test "Dense Vector death test" "")
add_check(core/matrix/dense/dense_matrix/test       "Dense Matrix test" "MCNLA_USE_GTEST")
add_check(core/matrix/dense/dense_matrix/death_test "Dense Matrix death test" "")
add_check(core/matrix/dense/dense_cube/test         "Dense Cube test" "MCNLA_USE_GTEST")
add_check(core/matrix/dense/dense_cube/death_test   "Dense Cube death test" "")

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
