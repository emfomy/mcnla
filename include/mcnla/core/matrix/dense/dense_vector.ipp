////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_

#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <iomanip>

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
  : BaseType(dim0(length), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(dim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(dim0(length), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(dim0(sizes), stride, capacity) {}

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
  : BaseType(dim0(length), stride, value, offset) {}

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
/// @brief  Print to stream.
///
template <typename __Scalar>
std::ostream& operator<< ( std::ostream &out, const DenseVector<__Scalar> &vector ) {
  for ( index_t i = 0; i < vector.getLength(); ++i ) {
    out << std::setw(ios_width) << vector(i) << "  ";
  }
  return out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of internal index.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getNidx() const noexcept {
  return this->getNelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::getElemImpl
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) noexcept {
  return this->getElemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::getElemImpl
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) const noexcept {
  return this->getElemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::getPosImpl
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getPos(
    const index_t idx
) const noexcept {
  return this->getPosImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar>
typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::find(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->getLength());
  return IteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename DenseVector<_Scalar>::ConstIteratorType DenseVector<_Scalar>::find(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->getLength());
  return ConstIteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename DenseVector<_Scalar>::ConstIteratorType DenseVector<_Scalar>::cfind(
    const index_t idx
) const noexcept {
  return find(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar>
void DenseVector<_Scalar>::resize(
    const index_t length,
    const index_t stride
) noexcept {
  this->resizeImpl(length, stride);
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
/// @copydoc  mcnla::matrix::VectorWrapper::getLength
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getLengthImpl() const noexcept {
  return this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::dim0( const SizesType sizes ) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  dim0
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::dim0( const index_t length ) const noexcept {
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

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_
