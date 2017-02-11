////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hpp
/// @brief   The SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HPP_

#include <mcnla/isvd/former/svd_former.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::FormerWrapper
///
template <typename _Val>
Former<SvdFormerTag, _Val>::Former(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::initialize
///
template <typename _Val>
void Former<SvdFormerTag, _Val>::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_u_.reconstruct(nrow, dim_sketch);
  matrix_vt_.reconstruct(dim_sketch, ncol);
  gesvd_driver_.reconstruct(dim_sketch, ncol);

  vector_s_cut_  = vector_s_({0, rank});
  matrix_u_cut_  = matrix_u_("", {0, rank});
  matrix_vt_cut_ = matrix_vt_({0, rank}, "");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::form
///
template <typename _Val> template <class _Matrix>
void Former<SvdFormerTag, _Val>::formImpl(
    const _Matrix &matrix_a,
    const DenseMatrixRowMajor<ValType> &matrix_q
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return;
  }

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(),  std::make_tuple(nrow, ncol));
  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));

  time0_ = MPI_Wtime();

  // Vt := Q' * A
  la::gemm(matrix_q.t(), matrix_a, matrix_vt_);
  time1_ = MPI_Wtime();

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver_(matrix_vt_, vector_s_, matrix_w_, matrix_empty_);
  time2_ = MPI_Wtime();

  // U := Q * W
  la::gemm(matrix_q, matrix_w_, matrix_u_);
  time3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::outputName
///
///
template <typename _Val>
std::ostream&Former<SvdFormerTag, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::time
///
template <typename _Val>
double Former<SvdFormerTag, _Val>::timeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::time
///
template <typename _Val>
double Former<SvdFormerTag, _Val>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::time
///
template <typename _Val>
double Former<SvdFormerTag, _Val>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::time
///
template <typename _Val>
double Former<SvdFormerTag, _Val>::time3() const noexcept {
  return time3_-time2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::vectorS
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& Former<SvdFormerTag, _Val>::vectorSImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::matrixU
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& Former<SvdFormerTag, _Val>::matrixUImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::matrixVt
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& Former<SvdFormerTag, _Val>::matrixVtImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_vt_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
