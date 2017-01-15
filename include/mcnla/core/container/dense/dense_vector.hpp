////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/dense/dense_vector.hpp
/// @brief   The dense vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HPP_
#define MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HPP_

#include <mcnla/core/container/dense/dense_vector.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride
) noexcept
  : BaseType(toDim0(length), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(toDim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(length), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(toDim0(length), stride, value, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( const DenseVector &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( DenseVector &&other ) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( const DenseVector &other ) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( DenseVector &&other ) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of internal index.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::nidx() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::container::DenseVectorStorage::getElemImpl
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) noexcept {
  return this->getElemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::container::DenseVectorStorage::getElemImpl
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) const noexcept {
  return this->getElemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::container::DenseVectorStorage::posImpl
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar>
DenseVectorIterator<_Scalar> DenseVector<_Scalar>::find(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->length());
  return IteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
DenseVectorConstIterator<_Scalar> DenseVector<_Scalar>::find(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->length());
  return ConstIteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
DenseVectorConstIterator<_Scalar> DenseVector<_Scalar>::cfind(
    const index_t idx
) const noexcept {
  return find(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the vector.
///
/// @attention  The data is also reallocated.
///
template <typename _Scalar> template <typename... Args>
void DenseVector<_Scalar>::reconstruct(
    Args... args
) noexcept {
  *this = DenseVector<_Scalar>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::container::DenseVectorStorage::resizeImpl
///
template <typename _Scalar>
void DenseVector<_Scalar>::resize(
    const index_t length,
    const index_t stride
) noexcept {
  this->resizeImpl(length, stride);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>& DenseVector<_Scalar>::viewDiagonal() noexcept {
  return static_cast<DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Scalar>
const DenseDiagonalMatrix<_Scalar>& DenseVector<_Scalar>::viewDiagonal() const noexcept {
  return static_cast<const DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar>
DenseVector<_Scalar> DenseVector<_Scalar>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar>
const DenseVector<_Scalar> DenseVector<_Scalar>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::container::VectorWrapper::length
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::lengthImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::toDim0(
    const index_t length
) const noexcept {
  return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>& DenseVector<_Scalar>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar>& DenseVector<_Scalar>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HPP_
