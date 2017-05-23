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
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase(
    const index_t size
) noexcept
  : BaseType(size, size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, size, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, size, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase(
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
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::DenseSymmetricMatrixBase(
    const DerivedType &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
SyMatS<_Core, DenseTag, _Val, _trans, _uplo>& DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
SyMatS<_Core, DenseTag, _Val, _trans, _uplo> DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::copy() const noexcept {
  DenseSymmetricMatrixBase retval(this->size(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::nnz() const noexcept {
  return !isUnitDiag(_uplo) ? (this->size()*(this->size()+1)/2) : (this->size()*(this->size()-1)/2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
_Val DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::operator()(
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
template <class _Core, typename _Val, Trans _trans, Uplo _uplo> template <typename... Args>
void DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::reconstruct(
    Args... args
) noexcept {
  *this = DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
void DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::resize(
    const index_t size
) noexcept {
  this->resizeImpl(size, size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
SyMatS<_Core, DenseTag, _Val, changeTrans(_trans), changeUplo(_uplo)>&
    DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
const SyMatS<_Core, DenseTag, _Val, changeTrans(_trans), changeUplo(_uplo)>&
    DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the general view of the matrix.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
GeMatS<_Core, DenseTag, _Val, _trans>&
    DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::viewGeneral() noexcept {
  return static_cast<GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewGeneral
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
const GeMatS<_Core, DenseTag, _Val, _trans>&
    DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::viewGeneral() const noexcept {
  return static_cast<const GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mrow
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::mrowImpl() const noexcept {
  return !isTrans(_trans) ? this->mdim0() : this->mdim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mcol
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrixBase<_Core, _Val, _trans, _uplo>::mcolImpl() const noexcept {
  return !isTrans(_trans) ? this->mdim1() : this->mdim0();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_BASE_HPP_
