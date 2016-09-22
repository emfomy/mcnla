////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector.ipp
/// @brief   The implementation of COO vector.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_IPP_
#define ISVD_MATRIX_COO_COO_VECTOR_IPP_

#include <isvd/matrix/coo/coo_vector.hpp>
#include <cmath>
#include <iomanip>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector() noexcept
  : VectorBaseType(),
    CooBaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length
) noexcept
  : VectorBaseType(length),
    CooBaseType(length) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t capability
) noexcept
  : VectorBaseType(length),
    CooBaseType(capability) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    const index_t capability,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, capability, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    const ValuePtrType &value,
    const IdxPtrType &idx,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, value, {idx}, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    const DataType &data,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, data, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector( const CooVector &other ) noexcept
  : VectorBaseType(other),
    CooBaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector( CooVector &&other ) noexcept
  : VectorBaseType(std::move(other)),
    CooBaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
CooVector<_Scalar>& CooVector<_Scalar>::operator=( const CooVector &other ) noexcept {
  VectorBaseType::operator=(other); CooBaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
CooVector<_Scalar>& CooVector<_Scalar>::operator=( CooVector &&other ) noexcept {
  VectorBaseType::operator=(std::move(other)); CooBaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar>
std::ostream& operator<< ( std::ostream &out, const CooVector<__Scalar> &vector ) {
  for ( auto it = vector.begin(); it != vector.end(); ++it ) {
    out << it;
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index array.
///
template <typename _Scalar>
index_t* CooVector<_Scalar>::getIdx() noexcept {
  return CooBaseType::template getIdx<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <typename _Scalar>
const index_t* CooVector<_Scalar>::getIdx() const noexcept {
  return CooBaseType::template getIdx<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar CooVector<_Scalar>::getElem(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  auto it = find(idx);
  return (it != this->end()) ? it.getValue() : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
_Scalar CooVector<_Scalar>::operator()(
    const index_t idx
) const noexcept { return getElem(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
//
/// @attention  Returns `-1` if the index does not exist!
///
template <typename _Scalar>
index_t CooVector<_Scalar>::getPos(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  auto it = find(idx);
  return (it != this->end()) ? it.getPos() : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position and nonzero elements of given index range.
///
template <typename _Scalar>
void CooVector<_Scalar>::getPosNnz(
    const IdxRange range,
          index_t &pos,
          index_t &nnz
) const noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  assert(isSorted());
  auto it0 = std::lower_bound(this->begin(), this->end(), isvd::makeCooTuple(range.begin));
  auto it1 = std::lower_bound(it0, this->end(), isvd::makeCooTuple(range.end));
  pos = it0.getPos();
  nnz = it1.getPos() - pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar>
typename CooVector<_Scalar>::IteratorType CooVector<_Scalar>::find(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  assert(isSorted());
  auto tuple = makeCooTuple(idx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::find(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  assert(isSorted());
  auto tuple = makeCooTuple(idx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::cfind(
    const index_t idx
) const noexcept {
  return cfind(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sorts the vector.
///
template <typename _Scalar>
void CooVector<_Scalar>::sort() noexcept {
  std::sort(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the vector is sorted.
///
template <typename _Scalar>
bool CooVector<_Scalar>::isSorted() const noexcept {
  return std::is_sorted(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar>
void CooVector<_Scalar>::resize(
    const index_t length
) noexcept {
  assert(length >= 0);
  length_ = length;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_IPP_
