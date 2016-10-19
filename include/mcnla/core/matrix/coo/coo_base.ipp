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
    data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t capacity
) noexcept
  : SparseBaseType(),
    data_(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const index_t capacity
) noexcept
  : SparseBaseType(nnz),
    data_(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const ValueArrayType &value,
    const std::array<IdxArrayType, ndim> &idxs
) noexcept
  : SparseBaseType(nnz),
    data_(value, idxs) {
  mcnla_assert_ge(getValueCapacity(), nnz_);
  for ( index_t dim = 0; dim < ndim; ++dim ) {
    mcnla_assert_ge(getIdxCapacity(dim), nnz_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <class _Derived>
CooBase<_Derived>::CooBase(
    const index_t nnz,
    const DataType &data
) noexcept
  : SparseBaseType(nnz),
    data_(data) {
  mcnla_assert_ge(getValueCapacity(), nnz_);
  for ( index_t dim = 0; dim < ndim; ++dim ) {
    mcnla_assert_ge(getIdxCapacity(dim), nnz_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
CooBase<_Derived>::CooBase( const CooBase &other ) noexcept
  : SparseBaseType(other),
    data_(other.data_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
CooBase<_Derived>::CooBase( CooBase &&other ) noexcept
  : SparseBaseType(std::move(other)),
    data_(std::move(other.data_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
CooBase<_Derived>& CooBase<_Derived>::operator=( const CooBase &other ) noexcept {
  SparseBaseType::operator=(other); data_ = other.data_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
CooBase<_Derived>& CooBase<_Derived>::operator=( CooBase &&other ) noexcept {
  SparseBaseType::operator=(std::move(other)); data_ = std::move(other.data_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <class _Derived>
typename CooBase<_Derived>::DataType& CooBase<_Derived>::getData() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <class _Derived>
bool CooBase<_Derived>::isEmpty() const noexcept { return getValueArray().isEmpty(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getData
///
template <class _Derived>
const typename CooBase<_Derived>::DataType& CooBase<_Derived>::getData() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the value array.
///
template <class _Derived>
index_t CooBase<_Derived>::getValueCapacity() const noexcept { return getValueArray().getCapacity(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the value array.
///
template <class _Derived>
index_t CooBase<_Derived>::getValueOffset() const noexcept { return getValueArray().getOffset(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the index array.
///
template <class _Derived>
index_t CooBase<_Derived>::getIdxCapacity( const index_t dim ) const noexcept { return getIdxArray(dim).getCapacity(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the index array.
///
template <class _Derived>
index_t CooBase<_Derived>::getIdxOffset( const index_t dim ) const noexcept { return getIdxArray(dim).getOffset(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxCapacity
///
template <class _Derived> template <index_t _dim>
index_t CooBase<_Derived>::getIdxCapacity() const noexcept { return getIdxArray<_dim>().getCapacity(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxOffset
///
template <class _Derived> template <index_t _dim>
index_t CooBase<_Derived>::getIdxOffset() const noexcept { return getIdxArray<_dim>().getOffset(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <class _Derived>
typename CooBase<_Derived>::ScalarType* CooBase<_Derived>::getValue() noexcept {
  return *(getValueArray());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <class _Derived>
const typename CooBase<_Derived>::ScalarType* CooBase<_Derived>::getValue() const noexcept {
  return *(getValueArray());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <class _Derived>
typename CooBase<_Derived>::ValueArrayType& CooBase<_Derived>::getValueArray() noexcept {
  return getData().getValueArray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueArray
///
template <class _Derived>
const typename CooBase<_Derived>::ValueArrayType& CooBase<_Derived>::getValueArray() const noexcept {
  return getData().getValueArray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray.
///
template <class _Derived>
typename CooBase<_Derived>::ValueValarrayType& CooBase<_Derived>::getValueValarray() noexcept {
  return getValueArray().getValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueValarray
///
template <class _Derived>
const typename CooBase<_Derived>::ValueValarrayType& CooBase<_Derived>::getValueValarray() const noexcept {
  return getValueArray().getValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <class _Derived>
index_t* CooBase<_Derived>::getIdx( const index_t dim ) noexcept {
  return *(getIdxArray(dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <class _Derived>
const index_t* CooBase<_Derived>::getIdx( const index_t dim ) const noexcept {
  return *(getIdxArray(dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <class _Derived>
typename CooBase<_Derived>::IdxArrayType& CooBase<_Derived>::getIdxArray( const index_t dim ) noexcept {
  return getData().getIdxArray(dim);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxArray
///
template <class _Derived>
const typename CooBase<_Derived>::IdxArrayType& CooBase<_Derived>::getIdxArray( const index_t dim ) const noexcept {
  return getData().getIdxArray(dim);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray.
///
template <class _Derived>
typename CooBase<_Derived>::IdxValarrayType& CooBase<_Derived>::getIdxValarray( const index_t dim ) noexcept {
  return getIdxArray(dim).getValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxValarray
///
template <class _Derived>
const typename CooBase<_Derived>::IdxValarrayType& CooBase<_Derived>::getIdxValarray( const index_t dim ) const noexcept {
  return getIdxArray(dim).getValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <class _Derived> template <index_t _dim>
index_t* CooBase<_Derived>::getIdx() noexcept {
  return *(getIdxArray<_dim>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <class _Derived> template <index_t _dim>
const index_t* CooBase<_Derived>::getIdx() const noexcept {
  return *(getIdxArray<_dim>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <class _Derived> template <index_t _dim>
typename CooBase<_Derived>::IdxArrayType& CooBase<_Derived>::getIdxArray() noexcept {
  return getData().getIdxArray<_dim>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxArray
///
template <class _Derived> template <index_t _dim>
const typename CooBase<_Derived>::IdxArrayType& CooBase<_Derived>::getIdxArray() const noexcept {
  return getData().getIdxArray<_dim>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray.
///
template <class _Derived> template <index_t _dim>
typename CooBase<_Derived>::IdxValarrayType& CooBase<_Derived>::getIdxValarray() noexcept {
  return getIdxArray<_dim>().getValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxValarray
///
template <class _Derived> template <index_t _dim>
const typename CooBase<_Derived>::IdxValarrayType& CooBase<_Derived>::getIdxValarray() const noexcept {
  return getIdxArray<_dim>().getValarray();
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
