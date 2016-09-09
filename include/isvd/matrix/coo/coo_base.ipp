////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_base.ipp
/// @brief   The implementation of COO interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_BASE_IPP_
#define ISVD_MATRIX_COO_COO_BASE_IPP_

#include <isvd/matrix/coo/coo_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
CooBase<_Derived>::CooBase() noexcept
  : SparseBaseType(),
    offset_(0),
    data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t capability,
    const index_t offset
) noexcept
  : SparseBaseType(),
    offset_(offset),
    data_(capability) {
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t capability,
    const index_t nnz,
    std::shared_ptr<ScalarType> value,
    std::array<std::shared_ptr<index_t>, ndim> idx,
    const index_t offset
) noexcept
  : SparseBaseType(nnz),
    offset_(offset),
    data_(capability, value, idx) {
  assert(capability_ >= nnz_);
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const DenseData<ScalarType>& data,
    const index_t offset
) noexcept
  : SparseBaseType(nnz),
    offset_(offset),
    data_(data) {
  assert(data_.getCapability() >= nnz_);
  assert(offset_ >= 0 && offset_ <= data_.getCapability());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived>
CooBase<_Derived>::CooBase( const CooBase &other ) noexcept
  : SparseBaseType(other),
    offset_(other.offset_),
    data_(other.data_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
CooBase<_Derived>::CooBase( CooBase &&other ) noexcept
  : SparseBaseType(std::move(other)),
    offset_(other.offset_),
    data_(std::move(other.data_)) {
  other.offset_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <class _Derived>
CooBase<_Derived>& CooBase<_Derived>::operator=( const CooBase &other ) noexcept {
  SparseBaseType::operator=(other); offset_ = other.offset_; data_ = other.data_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
CooBase<_Derived>& CooBase<_Derived>::operator=( CooBase &&other ) noexcept {
  SparseBaseType::operator=(std::move(other)); offset_ = other.offset_; data_ = std::move(other.data_); other.offset_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of data array.
///
template <class _Derived>
index_t CooBase<_Derived>::getCapability() const noexcept { return getData().getCapability(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <class _Derived>
index_t CooBase<_Derived>::getOffset() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <class _Derived>
DenseData<typename CooBase<_Derived>::ScalarType>& CooBase<_Derived>::getData() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getData
///
template <class _Derived>
const DenseData<typename CooBase<_Derived>::ScalarType>& CooBase<_Derived>::getData() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <class _Derived>
typename CooBase<_Derived>::ScalarType* CooBase<_Derived>::getValue() noexcept {
  return getData().getValue() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <class _Derived>
const typename CooBase<_Derived>::ScalarType* CooBase<_Derived>::getValue() const noexcept {
  return getData().getValue() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index array.
///
template <class _Derived> template <index_t dim>
index_t* CooBase<_Derived>::getIdx() noexcept {
  return getData().getIdx<dim>() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <class _Derived> template <index_t dim>
const index_t* CooBase<_Derived>::getIdx() const noexcept {
  return getData().getIdx<dim>() + getOffset();
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_BASE_IPP_
