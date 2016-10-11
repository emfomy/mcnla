# The CMake setting of 'check/'

# GTEST
set(GTEST_ROOT "" CACHE PATH "The root path of Google Test.")
find_package(GTest REQUIRED)
if(GTEST_FOUND)
  set(INCS ${INCS} "${GTEST_INCLUDE_DIRS}")
  set(LIBS ${LIBS} "${GTEST_BOTH_LIBRARIES}")
endif()

# Add check folders
include(check.cmake)
add_check(core_matrix "Matrix Module test")
# add_check(core_blas   "BLAS Module test")

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Running tests"
)
