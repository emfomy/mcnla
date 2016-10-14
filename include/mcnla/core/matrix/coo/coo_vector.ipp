////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector.ipp
/// @brief   The implementation of COO vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_IPP_

#include <mcnla/core/matrix/coo/coo_vector.hpp>
#include <cmath>
#include <iomanip>
#include <algorithm>

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
    const index_t capacity
) noexcept
  : VectorBaseType(length),
    CooBaseType(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    const index_t capacity
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    const ValueArrayType &value,
    const IdxArrayType &idx
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, value, {idx}) {}

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
    CooBaseType(nnz, data >> offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
  mcnla_assert_gelt(idx, 0, length_);
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
  mcnla_assert_gelt(idx, 0, length_);
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
  mcnla_assert_gele(range.begin, 0, length_); mcnla_assert_ge(range.getLength(), 0);
  mcnla_assert_true(isSorted());
  auto it0 = std::lower_bound(this->begin(), this->end(), makeCooTuple(range.begin));
  auto it1 = std::lower_bound(it0, this->end(), makeCooTuple(range.end));
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
  mcnla_assert_gelt(idx, 0, length_);
  mcnla_assert_true(isSorted());
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
  mcnla_assert_gelt(idx, 0, length_);
  mcnla_assert_true(isSorted());
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
  mcnla_assert_ge(length, 0);
  length_ = length;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_IPP_
