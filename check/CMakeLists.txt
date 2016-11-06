# The CMake setting of 'check/'

# Break
if(NOT MCNLA_BUILD_TEST)
  return()
endif()

# GTEST
set(GTEST_ROOT "" CACHE PATH "The root path of Google Test.")
find_package(GTest 1.8 REQUIRED)
if(GTEST_FOUND)
  list(APPEND INCS "${GTEST_INCLUDE_DIRS}")
  list(APPEND LIBS "${GTEST_BOTH_LIBRARIES}")
endif()

list(APPEND DEFS "-DMCNLA_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")

# Add check folders
include(check.cmake)
add_check_test(core/matrix/dense/dense_vector  "Dense Vector test")
add_check_death(core/matrix/dense/dense_vector "Dense Vector death test")
add_check_test(core/matrix/dense/dense_matrix  "Dense Matrix test")
add_check_death(core/matrix/dense/dense_matrix "Dense Matrix death test")
add_check_test(core/matrix/dense/dense_cube    "Dense Cube test")
add_check_death(core/matrix/dense/dense_cube   "Dense Cube death test")

add_mpi_check(isvd/integrator/kolmogorov_nagumo_integrator "Kolmogorov-Nagumo-type Integrator test" "KolmogorovNagumoIntegratorTest" 1 2 3 4 6 8 12 24)
add_mpi_check(isvd/integrator/naive_kolmogorov_nagumo_integrator "Naive Kolmogorov-Nagumo-type Integrator test" "NaiveKolmogorovNagumoIntegratorTest" 1 2 3 4 6 8 12 24)
add_mpi_check(isvd/integrator/reduction_integrator "Reduction Integrator test" "ReductionIntegratorTest" 1 2 4 8 16)

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
