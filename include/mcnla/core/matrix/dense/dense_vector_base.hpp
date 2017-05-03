////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_base.hpp
/// @brief   The dense vector base.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_vector_base.hh>

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
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase(
    const index_t length,
    const index_t stride
) noexcept
  : BaseType(toDim0(length), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(toDim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(length), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase(
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
template <typename _Val, class _Types>
DenseVectorBase<_Val, _Types>::DenseVectorBase( const DerivedType &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, class _Types>
typename DenseVectorBase<_Val, _Types>::DerivedType& DenseVectorBase<_Val, _Types>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the vector.
///
template <typename _Val, class _Types>
typename DenseVectorBase<_Val, _Types>::DerivedType DenseVectorBase<_Val, _Types>::copy() const noexcept {
  DenseVectorBase retval(this->length(), this->stride(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, class _Types>
index_t DenseVectorBase<_Val, _Types>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <typename _Val, class _Types>
_Val& DenseVectorBase<_Val, _Types>::operator()(
    const index_t idx
) noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <typename _Val, class _Types>
const _Val& DenseVectorBase<_Val, _Types>::operator()(
    const index_t idx
) const noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::posImpl
///
template <typename _Val, class _Types>
index_t DenseVectorBase<_Val, _Types>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the vector.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, class _Types> template <typename... Args>
void DenseVectorBase<_Val, _Types>::reconstruct(
    Args... args
) noexcept {
  *this = DenseVectorBase<_Val, _Types>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::resizeImpl
///
template <typename _Val, class _Types>
void DenseVectorBase<_Val, _Types>::resize(
    const index_t length
) noexcept {
  this->resizeImpl(length, this->stride());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::resizeImpl
///
template <typename _Val, class _Types>
void DenseVectorBase<_Val, _Types>::resize(
    const index_t length,
    const index_t stride
) noexcept {
  this->resizeImpl(length, stride);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <typename _Val, class _Types>
typename DenseVectorBase<_Val, _Types>::DiagonalType& DenseVectorBase<_Val, _Types>::viewDiagonal() noexcept {
  return static_cast<DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Val, class _Types>
const typename DenseVectorBase<_Val, _Types>::DiagonalType& DenseVectorBase<_Val, _Types>::viewDiagonal() const noexcept {
  return static_cast<const DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Val, class _Types>
typename DenseVectorBase<_Val, _Types>::DerivedType DenseVectorBase<_Val, _Types>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Val, class _Types>
const typename DenseVectorBase<_Val, _Types>::DerivedType DenseVectorBase<_Val, _Types>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::VectorWrapper::length
///
template <typename _Val, class _Types>
index_t DenseVectorBase<_Val, _Types>::lengthImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Val, class _Types>
index_t DenseVectorBase<_Val, _Types>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Val, class _Types>
index_t DenseVectorBase<_Val, _Types>::toDim0(
    const index_t length
) const noexcept {
  return length;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HPP_
