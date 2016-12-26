////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.ipp
/// @brief   The implementation of dense diagonal matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_IPP_

#include <mcnla/core/matrix/dense/dense_diagonal_matrix.hpp>

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
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(size, pitch+1, value, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
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
index_t DenseDiagonalMatrix<_Scalar>::getSize() const noexcept {
  return this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar>
_Scalar DenseDiagonalMatrix<_Scalar>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  return (rowidx == colidx) ? this->getElemImpl(rowidx) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar>
const _Scalar DenseDiagonalMatrix<_Scalar>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return (rowidx == colidx) ? this->getElemImpl(rowidx) : 0;
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
DenseDiagonalMatrix<_Scalar>&
    DenseDiagonalMatrix<_Scalar>::t() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Scalar>
const DenseDiagonalMatrix<_Scalar>&
    DenseDiagonalMatrix<_Scalar>::t() const noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNrow
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::getNrowImpl() const noexcept {
  return this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNcol
///
template <typename _Scalar>
index_t DenseDiagonalMatrix<_Scalar>::getNcolImpl() const noexcept {
  return this->getDim0();
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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_IPP_
