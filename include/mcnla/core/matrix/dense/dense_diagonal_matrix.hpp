////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.hpp
/// @brief   The dense diagonal matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_

#include <mcnla/core/matrix/dense/dense_diagonal_matrix.hh>

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
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
    const index_t size
) noexcept
  : BaseType(size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, pitch+1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, pitch+1, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
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
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
    const DenseDiagonalMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>::DenseDiagonalMatrix(
    DenseDiagonalMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>& DenseDiagonalMatrix<_Val>::operator=(
    const DenseDiagonalMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>& DenseDiagonalMatrix<_Val>::operator=(
    DenseDiagonalMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val>
DenseDiagonalMatrix<_Val> DenseDiagonalMatrix<_Val>::copy() const noexcept {
  DenseDiagonalMatrix retval(this->sizes(), this->pitch(), this->capacity());
  retval.val().valarray() = this->val().valarray();
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Val>
index_t DenseDiagonalMatrix<_Val>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val>
index_t DenseDiagonalMatrix<_Val>::nnz() const noexcept {
  return this->size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <typename _Val>
index_t DenseDiagonalMatrix<_Val>::pitch() const noexcept {
  return this->stride()-1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val>
_Val DenseDiagonalMatrix<_Val>::operator()(
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
template <typename _Val> template <typename... Args>
void DenseDiagonalMatrix<_Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseDiagonalMatrix<_Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val>
DenseDiagonalMatrix<_Val>& DenseDiagonalMatrix<_Val>::t() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val>
const DenseDiagonalMatrix<_Val>& DenseDiagonalMatrix<_Val>::t() const noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector view of the matrix.
///
template <typename _Val>
DenseVector<_Val>& DenseDiagonalMatrix<_Val>::viewVector() noexcept {
  return static_cast<VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Val>
const DenseVector<_Val>& DenseDiagonalMatrix<_Val>::viewVector() const noexcept {
  return static_cast<const VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Val>
DenseVector<_Val>& DenseDiagonalMatrix<_Val>::vectorize() noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Val>
const DenseVector<_Val>& DenseDiagonalMatrix<_Val>::vectorize() const noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val>
index_t DenseDiagonalMatrix<_Val>::nrowImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val>
index_t DenseDiagonalMatrix<_Val>::ncolImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val>
DenseVectorStorage<_Val>& DenseDiagonalMatrix<_Val>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val>
const DenseVectorStorage<_Val>& DenseDiagonalMatrix<_Val>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_
