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
  mcnla_assert_ge(this->getNrow(), 0);
  mcnla_assert_ge(this->getNcol(), 0);
  mcnla_assert_ge(this->getNmat(), 0);
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
  mcnla_assert_ge(this->getNrow(), 0);
  mcnla_assert_ge(this->getNcol(), 0);
  mcnla_assert_ge(this->getNmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120( const DenseMatrixSet120 &other ) noexcept
  : BaseType(other),
    data_(other.data_),
    ncol_(other.ncol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120( DenseMatrixSet120 &&other ) noexcept
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
  BaseType::operator=(other); data_ = other.data_; ncol_ = other.ncol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>& DenseMatrixSet120<_Scalar>::operator=( DenseMatrixSet120 &&other ) noexcept {
  BaseType::operator=(std::move(other)); data_ = std::move(other.data_); ncol_ = other.ncol_; other.ncol_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Scalar>
bool DenseMatrixSet120<_Scalar>::isShrunk() const noexcept {
  return (data_.getNcol() % ncol_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Scalar>
DenseMatrix<_Scalar, Layout::ROWMAJOR>& DenseMatrixSet120<_Scalar>::getData() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getData
///
template <class _Scalar>
const DenseMatrix<_Scalar, Layout::ROWMAJOR>& DenseMatrixSet120<_Scalar>::getData() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a set of rows.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::getSubset( const IdxRange idxrange ) noexcept {
  return SetType(ncol_, data_.getCols(idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubset.
///
template <class _Scalar>
const DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::getSubset( const IdxRange idxrange ) const noexcept {
  return SetType(ncol_, data_.getCols(idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a set of rows.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::getMatrixRows( const IdxRange rowrange ) noexcept {
  return SetType(ncol_, data_.getRows(rowrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getMatrixRows.
///
template <class _Scalar>
const DenseMatrixSet120<_Scalar> DenseMatrixSet120<_Scalar>::getMatrixRows( const IdxRange rowrange ) const noexcept {
  return SetType(ncol_, data_.getRows(rowrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the set.
///
template <class _Scalar>
DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::unfold() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Scalar>
const DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::unfold() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNrow
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNrowImpl() const noexcept { return data_.getNrow(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNcol
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNcolImpl() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNmat
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNmatImpl() const noexcept { return data_.getNcol() / ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getMatrix
///
template <class _Scalar>
DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::getMatrixImpl( const index_t idx ) noexcept {
  mcnla_assert_gelt(idx, 0, this->getNmat());
  return data_.getCols({idx*ncol_, (idx+1)*ncol_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getMatrix
///
template <class _Scalar>
const DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::getMatrixImpl( const index_t idx ) const noexcept {
  mcnla_assert_gelt(idx, 0, this->getNmat());
  return data_.getCols({idx*ncol_, (idx+1)*ncol_});
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_
