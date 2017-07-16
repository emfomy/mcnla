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

# Set data path
list(APPEND DEFS "-DMCNLA_DATA_PATH=\"${PROJECT_SOURCE_DIR}/data\"")

# Add check tests
include(check.cmake)

# CPU tests
set(DEFS_TMP "${DEFS}")
list(REMOVE_ITEM DEFS "MCNLA_USE_GPU")

# Core
add_check_test(core/matrix/dense/dense_vector  "Dense Vector test")
add_check_death(core/matrix/dense/dense_vector "Dense Vector death test")
add_check_test(core/matrix/dense/dense_matrix  "Dense Matrix test")
add_check_death(core/matrix/dense/dense_matrix "Dense Matrix death test")

# Sketcher
add_mpi_check(isvd/sketcher/gaussian_projection_sketcher "Gaussian Projection Sketcher test" "GaussianProjectionSketcherTest" 1 2 3 4 6 12)
add_mpi_check(isvd/sketcher/row_block_gaussian_projection_sketcher "Row-Block Gaussian Projection Sketcher test" "RowBlockGaussianProjectionSketcherTest" 1 2 3 4 6 12)
add_mpi_check(isvd/sketcher/col_block_gaussian_projection_sketcher "Column-Block Gaussian Projection Sketcher test" "ColBlockGaussianProjectionSketcherTest" 1 2 3 4 6 12)

add_mpi_check(isvd/sketcher/column_sampling_sketcher "Column Sampling Sketcher test" "ColumnSamplingSketcherTest" 1 2 3 4 6 12)
add_mpi_check(isvd/sketcher/row_block_column_sampling_sketcher "Row-Block Column Sampling Sketcher test" "RowBlockColumnSamplingSketcherTest" 1 2 3 4 6 12)

# Orthogonalizer
add_mpi_check(isvd/orthogonalizer/qr_orthogonalizer "QR Orthogonalizer test" "QrOrthogonalizerTest" 1 2 3 4 6 12)

add_mpi_check(isvd/orthogonalizer/svd_orthogonalizer "SVD Orthogonalizer test" "SvdOrthogonalizerTest" 1 2 3 4 6 12)

add_mpi_check(isvd/orthogonalizer/gramian_orthogonalizer "Gramian Orthogonalizer test" "GramianOrthogonalizerTest" 1 2 3 4 6 12)
add_mpi_check(isvd/orthogonalizer/row_block_gramian_orthogonalizer "Row-Block Gramian Orthogonalizer test" "RowBlockGramianOrthogonalizerTest" 1 2 3 4 6 12)

# Integrator
add_mpi_check(isvd/integrator/kolmogorov_nagumo_integrator "Kolmogorov-Nagumo-Type Integrator test" "KolmogorovNagumoIntegratorTest" 1 2 3 4 6 12)
add_mpi_check(isvd/integrator/row_block_kolmogorov_nagumo_integrator "Row-Block Kolmogorov-Nagumo-Type Integrator test" "RowBlockKolmogorovNagumoIntegratorTest" 1 2 3 4 6 12)
add_mpi_check(isvd/integrator/row_block_gramian_kolmogorov_nagumo_integrator "Row-Block Gramian Kolmogorov-Nagumo-Type Integrator test" "RowBlockGramianKolmogorovNagumoIntegratorTest" 1 2 3 4 6 12)

add_mpi_check(isvd/integrator/row_block_wen_yin_integrator "Row-Block Wen-Yin Line Search Integrator test" "RowBlockWenYinIntegratorTest" 1 2 3 4 6 12)
add_mpi_check(isvd/integrator/row_block_gramian_wen_yin_integrator "Row-Block Gramian Wen-Yin Line Search Integrator test" "RowBlockGramianWenYinIntegratorTest" 1 2 3 4 6 12)

add_mpi_check(isvd/integrator/row_block_reduction_integrator "Row-Block Reduction Integrator test" "RowBlockReductionIntegratorTest" 1 2 3 4 6 12)

add_mpi_check(isvd/integrator/row_block_extrinsic_mean_integrator "Row-Block Extrinsic Mean Integrator test" "RowBlockExtrinsicMeanIntegratorTest" 1 2 3 4 6 12)

# Former
add_mpi_check(isvd/former/svd_former "SVD Former test" "SvdFormerTest" 1)

add_mpi_check(isvd/former/gramian_former "Gramian Former test" "GramianFormerTest" 1)
add_mpi_check(isvd/former/row_block_gramian_former "Row-BLock Gramian Former test" "RowBlockGramianFormerTest" 1 2 3 4 6 12)
add_mpi_check(isvd/former/col_block_gramian_former "Column-BLock Gramian Former test" "ColBlockGramianFormerTest" 1 2 3 4 6 12)

add_mpi_check(isvd/former/row_block_symmetric_former "Row-BLock Symmetric Former test" "RowBlockSymmetricFormerTest" 1 2 3 4 6 12)

set(DEFS "${DEFS_TMP}")
unset(DEFS_TMP)

# GPU tests
if(MCNLA_USE_GPU)
  add_mpi_check(isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu "GPU Row-Block Gaussian Projection Sketcher test" "RowBlockGaussianProjectionSketcherGPUTest" 1 2 3 4 6 12)
  add_mpi_check(isvd_gpu/sketcher/col_block_gaussian_projection_sketcher_gpu "GPU Column-Block Gaussian Projection Sketcher test" "ColBlockGaussianProjectionSketcherGPUTest" 1 2 3 4 6 12)
endif()

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
