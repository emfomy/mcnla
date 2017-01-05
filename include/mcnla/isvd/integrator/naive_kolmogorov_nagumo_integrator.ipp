////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.ipp
/// @brief   The implementation of naive Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_
#define MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_

#include <mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.hpp>
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
NaiveKolmogorovNagumoIntegrator<_Matrix>::NaiveKolmogorovNagumoIntegrator(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void NaiveKolmogorovNagumoIntegrator<_Matrix>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();
  iter_ = -1;

  const auto set_q_sizes = std::make_tuple(nrow, dim_sketch, num_sketch_each);
  if ( set_q_.sizes() != set_q_sizes ) {
    set_q_ = DenseMatrixSet120<ScalarType>(set_q_sizes);
  }

  const auto matrix_qc_sizes = std::make_tuple(nrow, dim_sketch);
  if ( matrix_qc_.sizes() != matrix_qc_sizes ) {
    matrix_qc_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }
  if ( matrix_x_.sizes() != matrix_qc_sizes ) {
    matrix_x_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }
  if ( matrix_tmp_.sizes() != matrix_qc_sizes ) {
    matrix_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }

  const auto matrix_b_sizes = std::make_tuple(dim_sketch, dim_sketch);
  if ( matrix_b_.sizes() != matrix_b_sizes ) {
    matrix_b_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_b_sizes);
  }
  if ( matrix_d_.sizes() != matrix_b_sizes ) {
    matrix_d_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_b_sizes);
  }
  if ( matrix_c_.sizes() != matrix_b_sizes ) {
    matrix_c_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_b_sizes);
  }

  const auto vector_e_sizes = dim_sketch;
  if ( vector_e_.sizes() != vector_e_sizes ) {
    vector_e_ = DenseVector<ScalarType>(vector_e_sizes);
  }

  const auto syev_sizes = dim_sketch;
  if ( syev_driver_.sizes() != syev_sizes ) {
    syev_driver_.resize(syev_sizes);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::integrate
///
template <class _Matrix>
void NaiveKolmogorovNagumoIntegrator<_Matrix>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_root        = parameters_.mpi_root;
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto max_iteration   = parameters_.getMaxIteration();
  const auto tolerance       = parameters_.getTolerance();

  // Broadcast Q0 to Qc
  if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
    blas::copy(set_q_.getPage(0), matrix_qc_);
  }
  mcnla::mpi::bcast(matrix_qc_, mpi_root, MPI_COMM_WORLD);

  bool is_converged = false;
  for ( iter_ = 0; iter_ < max_iteration && !is_converged; ++iter_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // X := 0; D := 0
    blas::memset0(matrix_x_);
    blas::memset0(matrix_d_);

    for ( index_t i = 0; i < num_sketch_each; ++i ) {
      // Bi := Qi' * Qc
      blas::gemm<Trans::TRANS, Trans::NORMAL>(1.0, set_q_.getPage(i), matrix_qc_, 0.0, matrix_b_);

      // D += Bi' * Bi
      blas::syrk<Trans::TRANS>(1.0, matrix_b_, 1.0, matrix_d_);

      // X += Qi * Bi
      blas::gemm<Trans::NORMAL, Trans::NORMAL>(1.0, set_q_.getPage(i), matrix_b_, 1.0, matrix_x_);
    }

    // X -= Qc * D
    blas::symm<Side::RIGHT>(-1.0, matrix_d_, matrix_qc_, 1.0, matrix_x_);

    // X /= N
    blas::scal(1.0/num_sketch, matrix_x_.vectorize());

    // Reduce sum X
    mpi::allreduce(matrix_x_, MPI_SUM, mpi_comm);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // B := I/4 - X' * X
    blas::syrk<Trans::TRANS>(-1.0, matrix_x_, 0.0, matrix_b_);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_b_(i, i) += 0.25;
    }

    // Compute the eigen-decomposition of B -> B' * E * B
    syev_driver_(matrix_b_, vector_e_);

    // B := E^(1/4) * B
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(std::pow(vector_e_(i), 0.25), matrix_b_.getRow(i));
    }

    // D := I/2 + B' * B
    blas::syrk<Trans::TRANS>(1.0, matrix_b_, 0.0, matrix_d_);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_d_(i, i) += 0.5;
    }

    // Compute the eigen-decomposition of D -> D' * E * D
    syev_driver_(matrix_d_, vector_e_);

    // B := D
    blas::copy(matrix_d_, matrix_b_);

    // D := E^(1/4) * D; B := E^(-1/4) * B
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(std::pow(vector_e_(i),  0.25), matrix_d_.getRow(i));
      blas::scal(std::pow(vector_e_(i), -0.25), matrix_b_.getRow(i));
    }

    // C := D' * D
    blas::syrk<Trans::TRANS>(1.0, matrix_d_, 0.0, matrix_c_);

    // inv(C) := B' * B
    blas::syrk<Trans::TRANS>(1.0, matrix_b_, 0.0, matrix_d_);

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qc := Qc * C
    blas::copy(matrix_qc_, matrix_tmp_);
    blas::symm<Side::RIGHT>(1.0, matrix_c_, matrix_tmp_, 0.0, matrix_qc_);

    // Qc += X * inv(C)
    blas::symm<Side::RIGHT>(1.0, matrix_d_, matrix_x_, 1.0, matrix_qc_);

    // ================================================================================================================== //
    // Check convergence
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      vector_e_(i) = std::sqrt(vector_e_(i)) - 1.0;
    }
    is_converged = !(blas::nrm2(vector_e_) / std::sqrt(dim_sketch) > tolerance);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::name
///
template <class _Matrix>
constexpr const char* NaiveKolmogorovNagumoIntegrator<_Matrix>::nameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getIter
///
template <class _Matrix>
index_t NaiveKolmogorovNagumoIntegrator<_Matrix>::getIterImpl() const noexcept {
  return iter_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
DenseMatrixSet120<ScalarT<NaiveKolmogorovNagumoIntegrator<_Matrix>>>&
    NaiveKolmogorovNagumoIntegrator<_Matrix>::getSetQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
const DenseMatrixSet120<ScalarT<NaiveKolmogorovNagumoIntegrator<_Matrix>>>&
    NaiveKolmogorovNagumoIntegrator<_Matrix>::getSetQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
DenseMatrix<ScalarT<NaiveKolmogorovNagumoIntegrator<_Matrix>>, Layout::ROWMAJOR>&
    NaiveKolmogorovNagumoIntegrator<_Matrix>::getMatrixQbarImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
const DenseMatrix<ScalarT<NaiveKolmogorovNagumoIntegrator<_Matrix>>, Layout::ROWMAJOR>&
    NaiveKolmogorovNagumoIntegrator<_Matrix>::getMatrixQbarImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_
