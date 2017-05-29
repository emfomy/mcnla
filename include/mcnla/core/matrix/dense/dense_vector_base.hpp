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
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase(
    const index_t len,
    const index_t stride
) noexcept
  : BaseType(toDim0(len), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(toDim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase(
    const index_t len,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(len), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase(
    const index_t len,
    const index_t stride,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(toDim0(len), stride, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
DenseVectorBase<_Core, _Val>::DenseVectorBase( const DerivedType &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
GeVecT<_Core, DenseTag, _Val>& DenseVectorBase<_Core, _Val>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the vector.
///
template <class _Core, typename _Val>
GeVecT<_Core, DenseTag, _Val> DenseVectorBase<_Core, _Val>::copy() const noexcept {
  DenseVectorBase retval(this->len(), this->stride(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <class _Core, typename _Val>
_Val& DenseVectorBase<_Core, _Val>::operator()(
    const index_t idx
) noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::elemImpl
///
template <class _Core, typename _Val>
const _Val& DenseVectorBase<_Core, _Val>::operator()(
    const index_t idx
) const noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::posImpl
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the vector.
///
/// @attention  The data is also reallocated.
///
template <class _Core, typename _Val> template <typename ..._Args>
void DenseVectorBase<_Core, _Val>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseVectorBase<_Core, _Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorStorage::resizeImpl
///
template <class _Core, typename _Val>
void DenseVectorBase<_Core, _Val>::resize(
    const index_t len
) noexcept {
  this->resizeImpl(len);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <class _Core, typename _Val>
DiMatT<_Core, DenseTag, _Val>& DenseVectorBase<_Core, _Val>::diag() noexcept {
  return static_cast<DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  diag
///
template <class _Core, typename _Val>
const DiMatT<_Core, DenseTag, _Val>& DenseVectorBase<_Core, _Val>::diag() const noexcept {
  return static_cast<const DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Core, typename _Val>
GeVecT<_Core, DenseTag, _Val> DenseVectorBase<_Core, _Val>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Core, typename _Val>
const GeVecT<_Core, DenseTag, _Val> DenseVectorBase<_Core, _Val>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::VectorWrapper::len
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::lenImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVectorWrapper::mlen
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::mlenImpl() const noexcept {
  return this->mdim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <class _Core, typename _Val>
index_t DenseVectorBase<_Core, _Val>::toDim0(
    const index_t len
) const noexcept {
  return len;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HPP_
