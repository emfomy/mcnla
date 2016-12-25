////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix.ipp
/// @brief   The implementation of dense triangular matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_IPP_

#include <mcnla/core/matrix/dense/dense_triangular_matrix.hpp>

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
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    const index_t size
) noexcept
  : BaseType(size, size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, size, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, size, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    const index_t size,
    const index_t pitch,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(size, size, pitch, value, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    const DenseTriangularMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>::DenseTriangularMatrix(
    DenseTriangularMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>& DenseTriangularMatrix<_Scalar, _trans, _uplo>::operator=(
    const DenseTriangularMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>& DenseTriangularMatrix<_Scalar, _trans, _uplo>::operator=(
    DenseTriangularMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseTriangularMatrix<_Scalar, _trans, _uplo>::getSize() const noexcept {
  return this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
_Scalar DenseTriangularMatrix<_Scalar, _trans, _uplo>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  if ( rowidx == colidx ) {
    return isUnitDiag(_uplo) ? 1 : this->getElemImpl(rowidx, colidx);
  } else if ( !(isUpper(_uplo) ^ (rowidx < colidx)) ) {
    return (!isTrans(_trans) ? this->getElemImpl(rowidx, colidx) : this->getElemImpl(colidx, rowidx));
  } else {
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const _Scalar DenseTriangularMatrix<_Scalar, _trans, _uplo>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  if ( rowidx == colidx ) {
    return isUnitDiag(_uplo) ? 1 : this->getElemImpl(rowidx, colidx);
  } else if ( !(isUpper(_uplo) ^ (rowidx < colidx)) ) {
    return (!isTrans(_trans) ? this->getElemImpl(rowidx, colidx) : this->getElemImpl(colidx, rowidx));
  } else {
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Scalar, Trans _trans, Uplo _uplo> template <typename... Args>
void DenseTriangularMatrix<_Scalar, _trans, _uplo>::reconstruct(
    Args... args
) noexcept {
  *this = DenseTriangularMatrix<_Scalar, _trans, _uplo>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
void DenseTriangularMatrix<_Scalar, _trans, _uplo>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  !isTrans(_trans) ? this->resizeImpl(nrow, ncol) : this->resizeImpl(ncol, nrow);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseTriangularMatrix<_Scalar, changeTrans(_trans), _uplo>&
    DenseTriangularMatrix<_Scalar, _trans, _uplo>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  transpose
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const DenseTriangularMatrix<_Scalar, changeTrans(_trans), _uplo>&
    DenseTriangularMatrix<_Scalar, _trans, _uplo>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNrow
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseTriangularMatrix<_Scalar, _trans, _uplo>::getNrowImpl() const noexcept {
  return !isTrans(_trans) ? this->getDim0() : this->getDim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNcol
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseTriangularMatrix<_Scalar, _trans, _uplo>::getNcolImpl() const noexcept {
  return !isTrans(_trans) ? this->getDim1() : this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseMatrixStorage<_Scalar>& DenseTriangularMatrix<_Scalar, _trans, _uplo>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const DenseMatrixStorage<_Scalar>& DenseTriangularMatrix<_Scalar, _trans, _uplo>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_IPP_
