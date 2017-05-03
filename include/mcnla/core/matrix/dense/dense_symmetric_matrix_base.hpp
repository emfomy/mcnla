////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix_base.hpp
/// @brief   The dense symmetric matrix base.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_symmetric_matrix_base.hh>

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
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase(
    const index_t size
) noexcept
  : BaseType(size, size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, size, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, size, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase(
    const index_t size,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(size, size, pitch, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DenseSymmetricMatrixBase(
    const DerivedType &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType&
  DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType
    DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::copy() const noexcept {
  DenseSymmetricMatrixBase retval(this->size(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::nnz() const noexcept {
  return !isUnitDiag(_uplo) ? (this->size()*(this->size()+1)/2) : (this->size()*(this->size()-1)/2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
_Val DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return ( !isTrans(_trans) ^ isUpper(_uplo) ^ (rowidx <= colidx) )
      ? this->elemImpl(rowidx, colidx) : this->elemImpl(colidx, rowidx);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types> template <typename... Args>
void DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::reconstruct(
    Args... args
) noexcept {
  *this = DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
void DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::resize(
    const index_t size
) noexcept {
  this->resizeImpl(size, size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::TransposeType&
    DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::TransposeType&
    DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the general view of the matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::GeneralType&
    DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::viewGeneral() noexcept {
  return static_cast<GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewGeneral
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::GeneralType&
    DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::viewGeneral() const noexcept {
  return static_cast<const GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseSymmetricMatrixBase<_Val, _trans, _uplo, _Types>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}
}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_BASE_HPP_
