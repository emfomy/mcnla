////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_base.ipp
/// @brief   The implementation of COO container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_BASE_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_BASE_IPP_

#include <mcnla/core/matrix/coo/coo_base.hpp>

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
    const index_t capability
) noexcept
  : SparseBaseType(),
    offset_(0),
    data_(capability) {
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const index_t capability,
    const index_t offset
) noexcept
  : SparseBaseType(nnz),
    offset_(offset),
    data_(capability) {
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const ValuePtrType &value,
    const std::array<IdxPtrType, ndim> &idxs,
    const index_t offset
) noexcept
  : SparseBaseType(nnz),
    offset_(offset),
    data_(value, idxs) {
  assert(offset_ >= 0);
  assert(data_.getCapability() >= nnz_ + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const DataType &data,
    const index_t offset
) noexcept
  : SparseBaseType(nnz),
    offset_(offset),
    data_(data) {
  assert(offset_ >= 0);
  assert(data_.getCapability() >= nnz_ + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
/// @copydoc  mcnla::matrix::CooData::getCapability
///
template <class _Derived>
index_t CooBase<_Derived>::getCapability() const noexcept { return getData().getCapability(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <class _Derived>
index_t CooBase<_Derived>::getOffset() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Derived>
void CooBase<_Derived>::setNnz( const index_t nnz ) noexcept { nnz_ = nnz; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <class _Derived>
typename CooBase<_Derived>::DataType& CooBase<_Derived>::getData() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getData
///
template <class _Derived>
const typename CooBase<_Derived>::DataType& CooBase<_Derived>::getData() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooData::getValue
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
/// @copydoc  mcnla::matrix::CooData::getIdx
///
template <class _Derived> template <index_t _dim>
index_t* CooBase<_Derived>::getIdx() noexcept {
  static_assert(_dim >= 0 && _dim < ndim, "Invalid dimension!");
  return getData().getIdx<_dim>() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <class _Derived> template <index_t _dim>
const index_t* CooBase<_Derived>::getIdx() const noexcept {
  static_assert(_dim >= 0 && _dim < ndim, "Invalid dimension!");
  return getData().getIdx<_dim>() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooData::getTuple
///
template <class _Derived>
typename CooBase<_Derived>::TupleType CooBase<_Derived>::getTuple( const index_t itidx ) noexcept {
  return getData().getTuple(itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTuple
///
template <class _Derived>
typename CooBase<_Derived>::ConstTupleType CooBase<_Derived>::getTuple( const index_t itidx ) const noexcept {
  return getData().getTuple(itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& CooBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& CooBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_BASE_IPP_
