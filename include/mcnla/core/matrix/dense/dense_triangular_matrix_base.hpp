////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix_base.hpp
/// @brief   The dense triangular matrix base.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_triangular_matrix_base.hh>

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
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase(
    const index_t size
) noexcept
  : BaseType(size, size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, size, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, size, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase(
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
DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DenseTriangularMatrixBase(
    const DerivedType &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType&
  DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::copy() const noexcept {
  DenseTriangularMatrixBase retval(this->size(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::nnz() const noexcept {
  return !isUnitDiag(_uplo) ? (this->size()*(this->size()+1)/2) : (this->size()*(this->size()-1)/2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
_Val DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  if ( rowidx == colidx ) {
    return isUnitDiag(_uplo) ? 1 : this->elemImpl(rowidx, colidx);
  } else if ( !(isUpper(_uplo) ^ (rowidx < colidx)) ) {
    return (!isTrans(_trans) ? this->elemImpl(rowidx, colidx) : this->elemImpl(colidx, rowidx));
  } else {
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types> template <typename... Args>
void DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::reconstruct(
    Args... args
) noexcept {
  *this = DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
void DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::resize(
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
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::TransposeType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::TransposeType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the general view of the matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::GeneralType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::viewGeneral() noexcept {
  return static_cast<GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewGeneral
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::GeneralType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::viewGeneral() const noexcept {
  return static_cast<const GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
index_t DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::BaseType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::BaseType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to derived class.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::derived() noexcept {
  return static_cast<DerivedType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
const typename DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::DerivedType&
    DenseTriangularMatrixBase<_Val, _trans, _uplo, _Types>::derived() const noexcept {
  return static_cast<const DerivedType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_BASE_HPP_
