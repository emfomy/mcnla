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
  : nrow_(0),
    ncol_(0),
    pitch_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(dim1_),
    value_(Malloc<_Type>(pitch_ * dim2_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrixData<_Type, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    value_(Malloc<_Type>(pitch_ * dim2_)) {
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
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    value_(value) {
  assert(pitch_ >= dim1_);
  value = nullptr;
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
index_t DenseMatrixData<_Type, _layout>::getNrow() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Type, Layout _layout>
index_t DenseMatrixData<_Type, _layout>::getNcol() const noexcept { return ncol_; }

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

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
