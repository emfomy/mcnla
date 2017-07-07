////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <mcnla/core/matrix/dense/dense_vector_iterator.hh>
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
/// @brief  Output to stream.
///
template <typename ..._Args>
std::ostream& operator<<(
    std::ostream &os,
    const DenseVectorIteratorBase<_Args...> &it
) noexcept {
  return os << "(" << std::setw(kOsIdxWidth) << it.idx() << ")  "
                   << std::setw(kOsValWidth) << it.val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, class _Vector>
_Val& DenseVectorIteratorBase<_Val, _Vector>::val() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nelem());
  return container_->valPtr()[pos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Val, class _Vector>
index_t DenseVectorIteratorBase<_Val, _Vector>::idx() const noexcept {
  return idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first dimension index.
///
template <typename _Val, class _Vector>
index_t DenseVectorIteratorBase<_Val, _Vector>::idx0() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, class _Vector>
index_t DenseVectorIteratorBase<_Val, _Vector>::pos() const noexcept {
  return container_->pos(itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element reference.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, class _Vector>
_Val& DenseVectorIteratorBase<_Val, _Vector>::elemRef() const noexcept {
  return val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element pointer.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, class _Vector>
_Val* DenseVectorIteratorBase<_Val, _Vector>::elemPtr() const noexcept {
  return &(val());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
