////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix.hpp
/// @brief   The dense symmetric matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_

#include <mcnla/core/matrix/dense/dense_symmetric_matrix.hh>

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
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    const index_t size
) noexcept
  : BaseType(size, size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, size, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, size, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    const index_t size,
    const index_t pitch,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(size, size, pitch, value, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    const DenseSymmetricMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>::DenseSymmetricMatrix(
    DenseSymmetricMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::operator=(
    const DenseSymmetricMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::operator=(
    DenseSymmetricMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrix<_Scalar, _trans, _uplo>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
_Scalar DenseSymmetricMatrix<_Scalar, _trans, _uplo>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return ( !isTrans(_trans) ^ isUpper(_uplo) ^ (rowidx <= colidx) )
      ? this->getElemImpl(rowidx, colidx) : this->getElemImpl(colidx, rowidx);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Scalar, Trans _trans, Uplo _uplo> template <typename... Args>
void DenseSymmetricMatrix<_Scalar, _trans, _uplo>::reconstruct(
    Args... args
) noexcept {
  *this = DenseSymmetricMatrix<_Scalar, _trans, _uplo>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
void DenseSymmetricMatrix<_Scalar, _trans, _uplo>::resize(
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
DenseSymmetricMatrix<_Scalar, changeTrans(_trans), changeUplo(_uplo)>&
    DenseSymmetricMatrix<_Scalar, _trans, _uplo>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const DenseSymmetricMatrix<_Scalar, changeTrans(_trans), changeUplo(_uplo)>&
    DenseSymmetricMatrix<_Scalar, _trans, _uplo>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the general view of the matrix.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseMatrix<_Scalar, _trans>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::viewGeneral() noexcept {
  return static_cast<GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewGeneral
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const DenseMatrix<_Scalar, _trans>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::viewGeneral() const noexcept {
  return static_cast<const GeneralType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrix<_Scalar, _trans, _uplo>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
index_t DenseSymmetricMatrix<_Scalar, _trans, _uplo>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
DenseMatrixStorage<_Scalar>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
const DenseMatrixStorage<_Scalar>& DenseSymmetricMatrix<_Scalar, _trans, _uplo>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_
