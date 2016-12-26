////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/dense_matrix_set_120.ipp
/// @brief   The implementation of the dense matrix set with dimension order [1 2 0].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_
#define MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_

#include <mcnla/core/matrix/set/dense_matrix_set_120.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120() noexcept
  : BaseType(),
    data_(),
    ncol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : BaseType(),
    data_(nrow, ncol*nmat),
    ncol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : DenseMatrixSet120(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    const index_t ncol,
    const MatrixType &data
) noexcept
  : BaseType(),
    data_(data),
    ncol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    const DenseMatrixSet120 &other
) noexcept
  : BaseType(other),
    data_(other.data_),
    ncol_(other.ncol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    DenseMatrixSet120 &&other
) noexcept
  : BaseType(std::move(other)),
    data_(std::move(other.data_)),
    ncol_(other.ncol_) {
  other.ncol_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>& DenseMatrixSet120<_Scalar>::operator=( const DenseMatrixSet120 &other ) noexcept {
  BaseType::operator=(other);
  data_ = other.data_;
  ncol_ = other.ncol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>& DenseMatrixSet120<_Scalar>::operator=( DenseMatrixSet120 &&other ) noexcept {
  BaseType::operator=(std::move(other));
  data_ = std::move(other.data_);
  ncol_ = other.ncol_; other.ncol_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Scalar>
bool DenseMatrixSet120<_Scalar>::isShrunk() const noexcept {
  return (data_.ncol() % ncol_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar>& DenseMatrixSet120<_Scalar>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar>& DenseMatrixSet120<_Scalar>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the set.
///
/// @attention  The data is also reallocated.
///
template <class _Scalar> template <typename... Args>
void DenseMatrixSet120<_Scalar>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixSet120<_Scalar>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a set of rows.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::operator()(
    const IdxRange &idxrange
) noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Scalar>
const DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a set of rows.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) noexcept {
  return SetType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const char*, const char* )
///
template <class _Scalar>
const DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) const noexcept {
  return SetType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the set.
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixSet120<_Scalar>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixSet120<_Scalar>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetWrapper::nrow
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::nrowImpl() const noexcept {
  return data_.nrow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetWrapper::ncol
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::ncolImpl() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetWrapper::nmat
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::nmatImpl() const noexcept {
  return ncol_ ? (data_.ncol() / ncol_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetWrapper::operator()( const index_t )
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixSet120<_Scalar>::getMatrixImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", {idx*ncol_, (idx+1)*ncol_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetWrapper::operator()( const index_t )
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixSet120<_Scalar>::getMatrixImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", {idx*ncol_, (idx+1)*ncol_});
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_
