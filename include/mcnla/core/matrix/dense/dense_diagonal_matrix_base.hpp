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
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase(
    const index_t size
) noexcept
  : BaseType(size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, pitch+1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, pitch+1, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase(
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
template <class _Core, typename _Val>
DenseDiagonalMatrixBase<_Core, _Val>::DenseDiagonalMatrixBase(
    const DenseDiagonalMatrixBase &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
DiMatS<_Core, DenseTag, _Val>& DenseDiagonalMatrixBase<_Core, _Val>::operator=(
    const DenseDiagonalMatrixBase &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <class _Core, typename _Val>
DiMatS<_Core, DenseTag, _Val> DenseDiagonalMatrixBase<_Core, _Val>::copy() const noexcept {
  DenseDiagonalMatrixBase retval(this->size(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::nnz() const noexcept {
  return this->size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::pitch() const noexcept {
  return this->stride()-1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <class _Core, typename _Val>
_Val DenseDiagonalMatrixBase<_Core, _Val>::operator()(
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
template <class _Core, typename _Val> template <typename ..._Args>
void DenseDiagonalMatrixBase<_Core, _Val>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseDiagonalMatrixBase<_Core, _Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <class _Core, typename _Val>
DiMatS<_Core, DenseTag, _Val>& DenseDiagonalMatrixBase<_Core, _Val>::t() noexcept {
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <class _Core, typename _Val>
const DiMatS<_Core, DenseTag, _Val>& DenseDiagonalMatrixBase<_Core, _Val>::t() const noexcept {
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector view of the matrix.
///
template <class _Core, typename _Val>
GeVecS<_Core, DenseTag, _Val>& DenseDiagonalMatrixBase<_Core, _Val>::vec() noexcept {
  return static_cast<VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vec
///
template <class _Core, typename _Val>
const GeVecS<_Core, DenseTag, _Val>& DenseDiagonalMatrixBase<_Core, _Val>::vec() const noexcept {
  return static_cast<const VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::nrowImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::ncolImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mrow
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::mrowImpl() const noexcept {
  return this->mdim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mcol
///
template <class _Core, typename _Val>
index_t DenseDiagonalMatrixBase<_Core, _Val>::mcolImpl() const noexcept {
  return this->mdim0();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HPP_
