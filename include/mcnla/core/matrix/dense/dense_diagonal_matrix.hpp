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
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    const index_t size
) noexcept
  : BaseType(size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, pitch+1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, pitch+1, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    const index_t size,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(size, pitch+1, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    const DenseDiagonalMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>::DenseDiagonalMatrix(
    DenseDiagonalMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>& DenseDiagonalMatrix<_Scalar>::operator=(
    const DenseDiagonalMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>& DenseDiagonalMatrix<_Scalar>::operator=(
    DenseDiagonalMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::nnz() const noexcept {
  return this->size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Scalar>
_Scalar DenseDiagonalMatrix<_Scalar>::operator()(
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
template <typename _Scalar> template <typename... Args>
void DenseDiagonalMatrix<_Scalar>::reconstruct(
    Args... args
) noexcept {
  *this = DenseDiagonalMatrix<_Scalar>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar>
DenseDiagonalMatrix<_Scalar>& DenseDiagonalMatrix<_Scalar>::t() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Scalar>
const DenseDiagonalMatrix<_Scalar>& DenseDiagonalMatrix<_Scalar>::t() const noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector view of the matrix.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseDiagonalMatrix<_Scalar>::viewVector() noexcept {
  return static_cast<VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Scalar>
const DenseVector<_Scalar>& DenseDiagonalMatrix<_Scalar>::viewVector() const noexcept {
  return static_cast<const VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewVector
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseDiagonalMatrix<_Scalar>::vectorize() noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Scalar>
const DenseVector<_Scalar>& DenseDiagonalMatrix<_Scalar>::vectorize() const noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::nrowImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::ncolImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>& DenseDiagonalMatrix<_Scalar>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar>& DenseDiagonalMatrix<_Scalar>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_
