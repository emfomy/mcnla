////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.hpp
/// @brief   The dense vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_

#include <mcnla/core/matrix/dense/dense_vector.hh>

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
template <typename _Val>
DenseVector<_Val>::DenseVector() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVector<_Val>::DenseVector(
    const index_t length,
    const index_t stride
) noexcept
  : BaseType(toDim0(length), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVector<_Val>::DenseVector(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(toDim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVector<_Val>::DenseVector(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(length), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVector<_Val>::DenseVector(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseVector<_Val>::DenseVector(
    const index_t length,
    const index_t stride,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(toDim0(length), stride, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseVector<_Val>::DenseVector( const DenseVector &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val>
DenseVector<_Val>::DenseVector( DenseVector &&other ) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseVector<_Val>& DenseVector<_Val>::operator=(
    const DenseVector &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val>
DenseVector<_Val>& DenseVector<_Val>::operator=(
    DenseVector &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the vector.
///
template <typename _Val>
DenseVector<_Val> DenseVector<_Val>::copy() const noexcept {
  DenseVector retval(this->sizes(), this->stride(), this->capacity());
  retval.val() = this->val().copy();
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val>
index_t DenseVector<_Val>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <typename _Val>
_Val& DenseVector<_Val>::operator()(
    const index_t idx
) noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <typename _Val>
const _Val& DenseVector<_Val>::operator()(
    const index_t idx
) const noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::posImpl
///
template <typename _Val>
index_t DenseVector<_Val>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Val>
DenseVectorIterator<_Val> DenseVector<_Val>::find(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->length());
  return IteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val>
DenseVectorConstIterator<_Val> DenseVector<_Val>::find(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->length());
  return ConstIteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val>
DenseVectorConstIterator<_Val> DenseVector<_Val>::cfind(
    const index_t idx
) const noexcept {
  return find(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the vector.
///
/// @attention  The data is also reallocated.
///
template <typename _Val> template <typename... Args>
void DenseVector<_Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseVector<_Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::resizeImpl
///
template <typename _Val>
void DenseVector<_Val>::resize(
    const index_t length
) noexcept {
  this->resizeImpl(length, this->stride());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::resizeImpl
///
template <typename _Val>
void DenseVector<_Val>::resize(
    const index_t length,
    const index_t stride
) noexcept {
  this->resizeImpl(length, stride);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>& DenseVector<_Val>::viewDiagonal() noexcept {
  return static_cast<DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Val>
const DenseDiagonalMatrix<_Val>& DenseVector<_Val>::viewDiagonal() const noexcept {
  return static_cast<const DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Val>
DenseVector<_Val> DenseVector<_Val>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Val>
const DenseVector<_Val> DenseVector<_Val>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::VectorWrapper::length
///
template <typename _Val>
index_t DenseVector<_Val>::lengthImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Val>
index_t DenseVector<_Val>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Val>
index_t DenseVector<_Val>::toDim0(
    const index_t length
) const noexcept {
  return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val>
DenseVectorStorage<_Val>& DenseVector<_Val>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val>
const DenseVectorStorage<_Val>& DenseVector<_Val>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
