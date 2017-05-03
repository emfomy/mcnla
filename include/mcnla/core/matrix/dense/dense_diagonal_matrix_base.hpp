////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix_base.hpp
/// @brief   The dense diagonal matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_diagonal_matrix_base.hh>

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
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase(
    const index_t size
) noexcept
  : BaseType(size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, pitch+1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, class _Types>
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, pitch+1, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, class _Types>
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase(
    const index_t size,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(size, pitch+1, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, class _Types>
DenseDiagonalMatrixBase<_Val, _Types>::DenseDiagonalMatrixBase(
    const DerivedType &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::DerivedType& DenseDiagonalMatrixBase<_Val, _Types>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::DerivedType DenseDiagonalMatrixBase<_Val, _Types>::copy() const noexcept {
  DenseDiagonalMatrixBase retval(this->size(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Val, class _Types>
index_t DenseDiagonalMatrixBase<_Val, _Types>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, class _Types>
index_t DenseDiagonalMatrixBase<_Val, _Types>::nnz() const noexcept {
  return this->size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <typename _Val, class _Types>
index_t DenseDiagonalMatrixBase<_Val, _Types>::pitch() const noexcept {
  return this->stride()-1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val, class _Types>
_Val DenseDiagonalMatrixBase<_Val, _Types>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return (rowidx == colidx) ? this->elemImpl(rowidx) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, class _Types> template <typename... Args>
void DenseDiagonalMatrixBase<_Val, _Types>::reconstruct(
    Args... args
) noexcept {
  *this = DenseDiagonalMatrixBase<_Val, _Types>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::TransposeType&
    DenseDiagonalMatrixBase<_Val, _Types>::t() noexcept {
  return this->derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, class _Types>
const typename DenseDiagonalMatrixBase<_Val, _Types>::TransposeType&
    DenseDiagonalMatrixBase<_Val, _Types>::t() const noexcept {
  return this->derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector view of the matrix.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::VectorType&
    DenseDiagonalMatrixBase<_Val, _Types>::viewVector() noexcept {
  return static_cast<VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Val, class _Types>
const typename DenseDiagonalMatrixBase<_Val, _Types>::VectorType&
    DenseDiagonalMatrixBase<_Val, _Types>::viewVector() const noexcept {
  return static_cast<const VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::VectorType&
    DenseDiagonalMatrixBase<_Val, _Types>::vectorize() noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Val, class _Types>
const typename DenseDiagonalMatrixBase<_Val, _Types>::VectorType&
    DenseDiagonalMatrixBase<_Val, _Types>::vectorize() const noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val, class _Types>
index_t DenseDiagonalMatrixBase<_Val, _Types>::nrowImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val, class _Types>
index_t DenseDiagonalMatrixBase<_Val, _Types>::ncolImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::BaseType&
    DenseDiagonalMatrixBase<_Val, _Types>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val, class _Types>
const typename DenseDiagonalMatrixBase<_Val, _Types>::BaseType&
    DenseDiagonalMatrixBase<_Val, _Types>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to derived class.
///
template <typename _Val, class _Types>
typename DenseDiagonalMatrixBase<_Val, _Types>::DerivedType&
    DenseDiagonalMatrixBase<_Val, _Types>::derived() noexcept {
  return static_cast<DerivedType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <typename _Val, class _Types>
const typename DenseDiagonalMatrixBase<_Val, _Types>::DerivedType&
    DenseDiagonalMatrixBase<_Val, _Types>::derived() const noexcept {
  return static_cast<const DerivedType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HPP_
