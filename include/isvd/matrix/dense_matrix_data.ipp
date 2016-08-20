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
template <typename _Scalar, Layout _layout, bool _is_block>
DenseMatrixData<_Scalar, _layout, _is_block>::DenseMatrixData() noexcept
  : nrow_(0),
    ncol_(0),
    pitch_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Scalar, Layout _layout, bool _is_block>
DenseMatrixData<_Scalar, _layout, _is_block>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(dim1_),
    value_(Malloc<_Scalar>(pitch_ * dim2_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Scalar, Layout _layout, bool _is_block>
DenseMatrixData<_Scalar, _layout, _is_block>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    value_(Malloc<_Scalar>(pitch_ * dim2_)) {
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout, bool _is_block>
DenseMatrixData<_Scalar, _layout, _is_block>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Scalar *&value
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
template <typename _Scalar, Layout _layout, bool _is_block>
DenseMatrixData<_Scalar, _layout, _is_block>::~DenseMatrixData() noexcept {
  if ( !_is_block ) {
    Free(value_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the storage layout.
///
template <typename _Scalar, Layout _layout, bool _is_block>
Layout DenseMatrixData<_Scalar, _layout, _is_block>::getLayout() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows.
///
template <typename _Scalar, Layout _layout, bool _is_block>
index_t DenseMatrixData<_Scalar, _layout, _is_block>::getNrow() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Scalar, Layout _layout, bool _is_block>
index_t DenseMatrixData<_Scalar, _layout, _is_block>::getNcol() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the leading dimension.
///
template <typename _Scalar, Layout _layout, bool _is_block>
index_t DenseMatrixData<_Scalar, _layout, _is_block>::getPitch() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Scalar, Layout _layout, bool _is_block>
_Scalar* DenseMatrixData<_Scalar, _layout, _is_block>::getValue() const noexcept { return value_; }

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
