////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/reduction_integrator.ipp
/// @brief   The implementation of reduction integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_IPP_
#define MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_IPP_

#include <mcnla/isvd/integrator/reduction_integrator.hpp>
#include <mcnla/core/utility/function.hpp>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::IntegratorBase
///
template <class _Matrix>
ReductionIntegrator<_Matrix>::ReductionIntegrator(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void ReductionIntegrator<_Matrix>::initializeImpl() noexcept {

  const auto nrow            = parameters_.getNrow();
  const auto num_sketch_each = parameters_.getNumSketchEach();
  const auto dim_sketch      = parameters_.getDimSketch();

  mcnla_assert_true(utility::isPowerOf2(parameters_.mpi_size));
  mcnla_assert_true(utility::isPowerOf2(num_sketch_each));
  mcnla_assert_eq(parameters_.mpi_root, 0);

  const auto cube_q_sizes = std::make_tuple(nrow, dim_sketch, num_sketch_each);
  if ( cube_q_.getSizes() != cube_q_sizes ) {
    cube_q_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_q_sizes);
  }

  const auto matrix_q_sizes = std::make_pair(nrow, dim_sketch);
  if ( matrix_q_tmp_.getSizes() != matrix_q_sizes ) {
    matrix_q_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_q_sizes);
  }
  if ( matrix_buffer_.getSizes() != matrix_q_sizes ) {
    matrix_buffer_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_q_sizes);
  }

  const auto matrix_u_sizes = std::make_pair(dim_sketch, dim_sketch);
  if ( matrix_u_.getSizes() != matrix_u_sizes ) {
    matrix_u_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_u_sizes);
  }
  if ( matrix_vt_.getSizes() != matrix_u_sizes ) {
    matrix_vt_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_u_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  if ( gesvd_driver_.getSizes() != matrix_u_sizes ) {
    gesvd_driver_.resize(matrix_u_sizes);
  }

  matrix_q_bar_ = matrix_empty_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::integrate
///
template <class _Matrix>
void ReductionIntegrator<_Matrix>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto mpi_rank        = mpi::getCommRank(mpi_comm);
  const auto num_sketch_each = parameters_.getNumSketchEach();
  const auto dim_sketch      = parameters_.getDimSketch();

  /// @todo  Uses column major.
  /// @todo  Uses computational routines of gesvd (applying U & V instead of generating)

  // In-node integrate.
  for ( index_t j = 1; j < num_sketch_each; j *= 2 ) {
    for ( index_t i = 0; i < num_sketch_each; i += 2*j ) {

      // U := Q(i)' * Q(i+j)
      blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, cube_q_.getPage(i), cube_q_.getPage(i+j), 0.0, matrix_u_);

      // Compute the SVD of U -> U * S * Vt
      gesvd_driver_(matrix_u_, vector_s_, matrix_empty_, matrix_vt_);

      // Q(i) := Q(i) * U + Q(i+j) * V
      blas::copy(cube_q_.getPage(i), matrix_buffer_);
      blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, matrix_buffer_, matrix_u_, 0.0, cube_q_.getPage(i));
      blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0, cube_q_.getPage(i+j), matrix_vt_, 1.0, cube_q_.getPage(i));

      // Q(i) /= sqrt(2(I+S))
      for ( index_t k = 0; k < dim_sketch; ++k ) {
        blas::scal(1.0 / sqrt(2.0 * vector_s_(k) + 2.0), cube_q_.getPage(i).getCol(k));
      }

    }
  }

  matrix_q_bar_ = cube_q_.getPage(0);
  MPI_Status status;

  // Cross-node integrate.
  for ( index_t j = 1; j < mpi_size; j *= 2 ) {

    // Transfer Qbar -> Qtmp
    if ( mpi_rank % (2*j) == 0 ) {
      mpi::recv(matrix_q_tmp_, mpi_rank+j, 0, mpi_comm, status);
    } else {
      mpi::send(matrix_q_bar_, mpi_rank-j, 0, mpi_comm);
      return;
    }

    // U := Qbar' * Qtmp
    blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_q_bar_, matrix_q_tmp_, 0.0, matrix_u_);

    // Compute the SVD of U -> U * S * Vt
    gesvd_driver_(matrix_u_, vector_s_, matrix_empty_, matrix_vt_);

    // Q(i) := Q(i) * U + Q(i+j) * V
    blas::copy(matrix_q_bar_, matrix_buffer_);
    blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, matrix_buffer_, matrix_u_, 0.0, matrix_q_bar_);
    blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0, matrix_q_tmp_, matrix_vt_, 1.0, matrix_q_bar_);

    // Q(i) /= sqrt(2(I+S))
    for ( index_t k = 0; k < dim_sketch; ++k ) {
      blas::scal(1.0 / sqrt(2.0 * vector_s_(k) + 2.0), matrix_q_bar_.getCol(k));
    }

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getName
///
template <class _Matrix>
constexpr const char* ReductionIntegrator<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getIter
///
template <class _Matrix>
index_t ReductionIntegrator<_Matrix>::getIterImpl() const noexcept {
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getCubeQ
///
template <class _Matrix>
DenseCube<typename ReductionIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ReductionIntegrator<_Matrix>::getCubeQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return cube_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getCubeQ
///
template <class _Matrix>
const DenseCube<typename ReductionIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ReductionIntegrator<_Matrix>::getCubeQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return cube_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
DenseMatrix<typename ReductionIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ReductionIntegrator<_Matrix>::getMatrixQbarImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_q_bar_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
const DenseMatrix<typename ReductionIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ReductionIntegrator<_Matrix>::getMatrixQbarImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_q_bar_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_IPP_