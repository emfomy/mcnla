////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_data.ipp
/// @brief   The implementation of dense matrix data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
#define ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_

#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/utility/memory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default constructor.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData() noexcept
  : dim1_(0),
    dim2_(0),
    pitch_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol
) noexcept {
  setNrow(*this, nrow);
  setNcol(*this, ncol);
  pitch_ = dim1_;
  value_ = Malloc<_Type>(pitch_ * dim2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept {
  setNrow(*this, nrow);
  setNcol(*this, ncol);
  pitch_ = pitch;
  value_ = Malloc<_Type>(pitch_ * dim2_);
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given raw data.
///
/// @attention  DO NOT FREE #value!!
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Type *&value
) noexcept {
  setNrow(*this, nrow);
  setNcol(*this, ncol);
  pitch_ = pitch;
  value_ = value;
  value = nullptr;
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default destructor.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::~DenseMatrixData() noexcept {
  Free(value_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the storage layout.
///
template <typename _Type, Layout _layout>
Layout DenseMatrixData<_Type, _layout>::getLayout() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNrow() const noexcept { return getNrow(*this); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNcol() const noexcept { return getNcol(*this); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the leading dimension.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getPitch() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Type, Layout _layout>
_Type* DenseMatrixData<_Type, _layout>::getValue() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows of a column-major matrix.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNrow(
    const DenseMatrixData<_Type, Layout::COLMAJOR> &data
) noexcept {
  return data.dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows of a row-major matrix.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNrow(
    const DenseMatrixData<_Type, Layout::ROWMAJOR> &data
) noexcept {
  return data.dim2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns of a column-major matrix.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNcol(
    const DenseMatrixData<_Type, Layout::COLMAJOR> &data
) noexcept {
  return data.dim2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns of a row-major matrix.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNcol(
    const DenseMatrixData<_Type, Layout::ROWMAJOR> &data
) noexcept {
  return data.dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sets the number of rows of a column-major matrix.
///
template <typename _Type, Layout _layout>
void DenseMatrixData<_Type, _layout>::setNrow(
    DenseMatrixData<_Type, Layout::COLMAJOR> &data,
    const index_t row
) noexcept {
  data.dim1_ = row;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sets the number of rows of a row-major matrix.
///
template <typename _Type, Layout _layout>
void DenseMatrixData<_Type, _layout>::setNrow(
    DenseMatrixData<_Type, Layout::ROWMAJOR> &data,
    const index_t row
) noexcept {
  data.dim2_ = row;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sets the number of columns of a column-major matrix.
///
template <typename _Type, Layout _layout>
void DenseMatrixData<_Type, _layout>::setNcol(
    DenseMatrixData<_Type, Layout::COLMAJOR> &data,
    const index_t col
) noexcept {
  data.dim2_ = col;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sets the number of columns of a row-major matrix.
///
template <typename _Type, Layout _layout>
void DenseMatrixData<_Type, _layout>::setNcol(
    DenseMatrixData<_Type, Layout::ROWMAJOR> &data,
    const index_t col
) noexcept {
  data.dim1_ = col;
}

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
