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
    const index_t capability,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    CooBaseType(capability, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    std::shared_ptr<_Scalar> value,
    std::shared_ptr<index_t> idx
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, nnz, value, {idx}) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooVector<_Scalar>::CooVector(
    const index_t length,
    const index_t nnz,
    std::shared_ptr<_Scalar> value,
    std::shared_ptr<index_t> idx,
    const index_t capability,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    CooBaseType(nnz, capability, value, {idx}, offset) {}

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
  std::string str;
  const index_t witdh = log10(vector.length_)+1;
  for ( auto it = vector.cbegin(); it != vector.cend(); ++it ) {
    out << "(" << std::setw(witdh) << it.getIdx() << ")  " << std::setw(ios_width) << *it << std::endl;
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
  auto it = getIterator(idx);
  return (it != end()) ? *it : 0;
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
/// @attention  Returns @c -1 if the index does not exist!
///
template <typename _Scalar>
index_t CooVector<_Scalar>::getPos(
    const index_t idx
) const noexcept {
  for ( auto it = begin() ; it != end(); ++it ) {
    if ( it.getIdx() == idx ) {
      return it.getPos();
    }
  }
  return -1;
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
  auto it = begin();
  for ( ; it != end(); ++it ) {
    if ( it.getIdx() >= range.begin ) {
      break;
    }
  }
  pos = it.getPos();

  for ( ; it != end(); ++it ) {
    if ( it.getIdx() >= range.end ) {
      break;
    }
  }
  nnz = it.getPos() - pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to beginning.
///
template <typename _Scalar>
typename CooVector<_Scalar>::IteratorType CooVector<_Scalar>::begin() noexcept {
  return IteratorType::getBegin(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::begin() const noexcept {
  return ConstIteratorType::getBegin(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::cbegin() const noexcept {
  return ConstIteratorType::getBegin(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <typename _Scalar>
typename CooVector<_Scalar>::IteratorType CooVector<_Scalar>::end() noexcept {
  return IteratorType::getEnd(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::end() const noexcept {
  return ConstIteratorType::getEnd(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::cend() const noexcept {
  return ConstIteratorType::getEnd(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator of given index.
///
template <typename _Scalar>
typename CooVector<_Scalar>::IteratorType CooVector<_Scalar>::getIterator(
    const index_t idx
) noexcept {
  auto it = begin();
  for ( ; it != end(); ++it ) {
    if ( it.getIdx() == idx ) {
      break;
    }
  }
  return it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIterator
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::getIterator(
    const index_t idx
) const noexcept {
  auto it = begin();
  for ( ; it != end(); ++it ) {
    if ( it.getIdx() == idx ) {
      break;
    }
  }
  return it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIterator
///
template <typename _Scalar>
typename CooVector<_Scalar>::ConstIteratorType CooVector<_Scalar>::getConstIterator(
    const index_t idx
) const noexcept {
  auto it = begin();
  for ( ; it != end(); ++it ) {
    if ( it.getIdx() == idx ) {
      break;
    }
  }
  return it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the vector.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar>
void CooVector<_Scalar>::resize(
    const index_t length
) noexcept {
  assert(length > 0 && length >= nnz_);
  length_ = length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector segment.
///
template <typename _Scalar>
CooVector<_Scalar> CooVector<_Scalar>::getSegment(
    const IdxRange range
) noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  index_t pos, nnz; getPosNnz(range, pos, nnz);
  return CooVector<_Scalar>(range.getLength(), nnz, data_, pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSegment
///
template <typename _Scalar>
const CooVector<_Scalar> CooVector<_Scalar>::getSegment(
    const IdxRange range
) const noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  index_t pos, nnz; getPosNnz(range, pos, nnz);
  return CooVector<_Scalar>(range.getLength(), nnz, data_, pos + offset_);
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_IPP_
