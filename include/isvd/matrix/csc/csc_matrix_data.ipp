////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/csc/csc_matrix_data.ipp
/// @brief   The implementation of CSC data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CSC_CSC_MATRIX_DATA_IPP_
#define ISVD_MATRIX_CSC_CSC_MATRIX_DATA_IPP_

#include <isvd/matrix/csc/csc_matrix_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
CscMatrixData<_Scalar>::CscMatrixData() noexcept
  : value_(kNullValue),
    idx0_(kNullIdx),
    ptr1_(kNullIdx) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CscMatrixData<_Scalar>::CscMatrixData(
    const index_t size0,
    const index_t capability
) noexcept
  : value_(new std::valarray<_Scalar>(capability)),
    idx0_(new std::valarray<index_t>(size0)),
    ptr1_(new std::valarray<index_t>(capability)) {
  assert(capability > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  The size of @a value and each element in @a idxs should be the same.
///
template <typename _Scalar>
CscMatrixData<_Scalar>::CscMatrixData(
    ValuePtrType value,
    IdxPtrType idx0,
    IdxPtrType ptr1
) noexcept
  : value_(value),
    idx0_(idx0),
    ptr1_(ptr1) {
  assert(value->size() == ptr1_->size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
CscMatrixData<_Scalar>::CscMatrixData( const CscMatrixData &other ) noexcept
  : value_(other.value_),
    idx0_(other.idx0_),
    ptr1_(other.ptr1_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
CscMatrixData<_Scalar>::CscMatrixData( CscMatrixData &&other ) noexcept
  : value_(std::move(other.value_)),
    idx0_(std::move(other.idx0_)),
    ptr1_(std::move(other.ptr1_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
CscMatrixData<_Scalar>& CscMatrixData<_Scalar>::operator=( const CscMatrixData &other ) noexcept {
  value_ = other.value_; idx0_ = other.idx0_; ptr1_ = other.ptr1_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
CscMatrixData<_Scalar>& CscMatrixData<_Scalar>::operator=( CscMatrixData &&other ) noexcept {
  value_ = std::move(other.value_); idx0_ = std::move(other.idx0_); ptr1_ = std::move(other.ptr1_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
_Scalar* CscMatrixData<_Scalar>::operator*() noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* CscMatrixData<_Scalar>::operator*() const noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar>
bool CscMatrixData<_Scalar>::operator==( const CscMatrixData& other ) const noexcept {
  return this->value_ == other.value_ && this->idx0_ == other.idx0_ && this->ptr1_ == other.ptr1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar>
bool CscMatrixData<_Scalar>::operator!=( const CscMatrixData& other ) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading size.
///
template <typename _Scalar>
index_t CscMatrixData<_Scalar>::getSize1() const noexcept { return ptr1_->size(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of value array.
///
template <typename _Scalar>
index_t CscMatrixData<_Scalar>::getCapability() const noexcept { return value_->size(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
_Scalar* CscMatrixData<_Scalar>::getValue() noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* CscMatrixData<_Scalar>::getValue() const noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index array.
///
template <typename _Scalar>
index_t* CscMatrixData<_Scalar>::getIdx0() noexcept { return &((*idx0_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx0
///
template <typename _Scalar>
const index_t* CscMatrixData<_Scalar>::getIdx0() const noexcept { return &((*idx0_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second pointer array.
///
template <typename _Scalar>
index_t* CscMatrixData<_Scalar>::getPtr1() noexcept { return &((*ptr1_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPtr1
///
template <typename _Scalar>
const index_t* CscMatrixData<_Scalar>::getPtr1() const noexcept { return &((*ptr1_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array pointer.
///
template <typename _Scalar>
std::shared_ptr<std::valarray<_Scalar>>& CscMatrixData<_Scalar>::getValuePtr() noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValuePtr
///
template <typename _Scalar>
const std::shared_ptr<std::valarray<_Scalar>>& CscMatrixData<_Scalar>::getValuePtr() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index array pointer.
///
template <typename _Scalar>
std::shared_ptr<std::valarray<index_t>>& CscMatrixData<_Scalar>::getIdx0Ptr() noexcept { return idx0_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx0Ptr
///
template <typename _Scalar>
const std::shared_ptr<std::valarray<index_t>>& CscMatrixData<_Scalar>::getIdx0Ptr() const noexcept { return idx0_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second pointer array pointer.
///
template <typename _Scalar>
std::shared_ptr<std::valarray<index_t>>& CscMatrixData<_Scalar>::getPtr1Ptr() noexcept { return ptr1_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPtr1Ptr
///
template <typename _Scalar>
const std::shared_ptr<std::valarray<index_t>>& CscMatrixData<_Scalar>::getPtr1Ptr() const noexcept { return ptr1_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reduces dimension.
///
template <typename _Scalar>
CooData<1, _Scalar> CscMatrixData<_Scalar>::getReduced() noexcept {
  return CooData<1, _Scalar>(value_, {idx0_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getReduced
///
template <typename _Scalar>
const CooData<1, _Scalar> CscMatrixData<_Scalar>::getReduced() const noexcept {
  return CooData<1, _Scalar>(value_, {idx0_});
}

}  // namespace isvd

#endif  // ISVD_MATRIX_CSC_CSC_MATRIX_DATA_IPP_
