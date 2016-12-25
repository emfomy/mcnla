////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.ipp
/// @brief   The implementation of dense matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_

#include <mcnla/core/matrix/dense/dense_matrix.hpp>

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
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : BaseType(dim0(nrow, ncol), dim1(nrow, ncol)) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const SizesType sizes
) noexcept
  : BaseType(dim0(sizes), dim1(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : BaseType(dim0(nrow, ncol), dim1(nrow, ncol), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const SizesType sizes,
    const index_t pitch
) noexcept
  : BaseType(dim0(sizes), dim1(sizes), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(dim0(nrow, ncol), dim1(nrow, ncol), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const SizesType sizes,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(dim0(sizes), dim1(sizes), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(dim0(nrow, ncol), dim1(nrow, ncol), pitch, value, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    const DenseMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>::DenseMatrix(
    DenseMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>& DenseMatrix<_Scalar, _trans>::operator=(
    const DenseMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans>& DenseMatrix<_Scalar, _trans>::operator=(
    DenseMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of internal index.
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::getNidx() const noexcept {
  return this->getNelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar, Trans _trans>
_Scalar& DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  return !isTrans(_trans) ? this->getElemImpl(rowidx, colidx) : this->getElemImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getElemImpl
///
template <typename _Scalar, Trans _trans>
const _Scalar& DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return !isTrans(_trans) ? this->getElemImpl(rowidx, colidx) : this->getElemImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getPosImpl
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::getPos(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return !isTrans(_trans) ? this->getPosImpl(rowidx, colidx) : this->getPosImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar, Trans _trans>
typename DenseMatrix<_Scalar, _trans>::IteratorType DenseMatrix<_Scalar, _trans>::find(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  mcnla_assert_gelt(rowidx, 0, this->getNrow());
  mcnla_assert_gelt(colidx, 0, this->getNcol());
  auto itidx = !isTrans(_trans) ? (rowidx + colidx * this->getDim0()) : (colidx + rowidx * this->getDim0());
  return IteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Trans _trans>
typename DenseMatrix<_Scalar, _trans>::ConstIteratorType DenseMatrix<_Scalar, _trans>::find(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  mcnla_assert_gelt(rowidx, 0, this->getNrow());
  mcnla_assert_gelt(colidx, 0, this->getNcol());
  auto itidx = !isTrans(_trans) ? (rowidx + colidx * this->getDim0()) : (colidx + rowidx * this->getDim0());
  return ConstIteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Trans _trans>
typename DenseMatrix<_Scalar, _trans>::ConstIteratorType DenseMatrix<_Scalar, _trans>::cfind(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return find(rowidx, colidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, changeTrans(_trans)>& DenseMatrix<_Scalar, _trans>::transpose() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  transpose
///
template <typename _Scalar, Trans _trans>
const DenseMatrix<_Scalar, changeTrans(_trans)>& DenseMatrix<_Scalar, _trans>::transpose() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the symmetric view of the matrix.
///
template <typename _Scalar, Trans _trans> template <Uplo _uplo>
DenseSymmetricMatrix<_Scalar, _trans, _uplo>& DenseMatrix<_Scalar, _trans>::viewSymmetric() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewSymmetric
///
template <typename _Scalar, Trans _trans> template <Uplo _uplo>
const DenseSymmetricMatrix<_Scalar, _trans, _uplo>& DenseMatrix<_Scalar, _trans>::viewSymmetric() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the triangular view of the matrix.
///
template <typename _Scalar, Trans _trans> template <Uplo _uplo>
DenseTriangularMatrix<_Scalar, _trans, _uplo>& DenseMatrix<_Scalar, _trans>::viewTriangular() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewTriangular
///
template <typename _Scalar, Trans _trans> template <Uplo _uplo>
const DenseTriangularMatrix<_Scalar, _trans, _uplo>& DenseMatrix<_Scalar, _trans>::viewTriangular() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <typename _Scalar, Trans _trans>
DenseDiagonalMatrix<_Scalar> DenseMatrix<_Scalar, _trans>::viewDiagonal() noexcept {
  mcnla_assert_true(this->isSquare());
  return getDiagonal().viewDiagonal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Scalar, Trans _trans>
const DenseDiagonalMatrix<_Scalar> DenseMatrix<_Scalar, _trans>::viewDiagonal() const noexcept {
  return getDiagonal().viewDiagonal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Scalar, Trans _trans>
void DenseMatrix<_Scalar, _trans>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  !isTrans(_trans) ? this->resizeImpl(nrow, ncol) : this->resizeImpl(ncol, nrow);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const IdxRange &colrange
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colrange) : this->getMatrixImpl(colrange, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
const DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colrange) : this->getMatrixImpl(colrange, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const char*,
    const IdxRange &colrange
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowfullrange(), colrange) : this->getMatrixImpl(colrange, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
const DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const char*,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowfullrange(), colrange) : this->getMatrixImpl(colrange, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const char*
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colfullrange()) : this->getMatrixImpl(colfullrange(), rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getMatrixImpl
///
template <typename _Scalar, Trans _trans>
const DenseMatrix<_Scalar, _trans> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const char*
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colfullrange()) : this->getMatrixImpl(colfullrange(), rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const index_t colidx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowrange, colidx) : this->getVector1Impl(colidx, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const IdxRange &rowrange,
    const index_t colidx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowrange, colidx) : this->getVector1Impl(colidx, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const char*,
    const index_t colidx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowfullrange(), colidx) : this->getVector1Impl(colidx, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const char*,
    const index_t colidx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowfullrange(), colidx) : this->getVector1Impl(colidx, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const IdxRange &colrange
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colrange) : this->getVector0Impl(colrange, rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colrange) : this->getVector0Impl(colrange, rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const char*
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colfullrange()) : this->getVector0Impl(colfullrange(), rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getVector0Impl
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::operator()(
    const index_t rowidx,
    const char*
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colfullrange()) : this->getVector0Impl(colfullrange(), rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getDiagonalImpl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::getDiagonal(
    const index_t idx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getDiagonalImpl(idx) : this->getDiagonalImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonal
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::getDiagonal(
    const index_t idx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getDiagonalImpl(idx) : this->getDiagonalImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::vectorizeImpl
///
template <typename _Scalar, Trans _trans>
DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::vectorize() noexcept {
  return static_cast<VectorType&&>(this->vectorizeImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Scalar, Trans _trans>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _trans>::vectorize() const noexcept {
  return static_cast<const VectorType&&>(this->vectorizeImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNrow
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::getNrowImpl() const noexcept {
  return !isTrans(_trans) ? this->getDim0() : this->getDim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::getNcol
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::getNcolImpl() const noexcept {
  return !isTrans(_trans) ? this->getDim1() : this->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::dim0(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<0>(sizes) : std::get<1>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  dim0
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::dim0(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? nrow : ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the second dimension from sizes.
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::dim1(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<1>(sizes) : std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  dim1
///
template <typename _Scalar, Trans _trans>
index_t DenseMatrix<_Scalar, _trans>::dim1(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? ncol : nrow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full row index range.
///
template <typename _Scalar, Trans _trans>
const IdxRange DenseMatrix<_Scalar, _trans>::rowfullrange() const noexcept {
  return {0, this->getNrow()};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full column index range.
///
template <typename _Scalar, Trans _trans>
const IdxRange DenseMatrix<_Scalar, _trans>::colfullrange() const noexcept {
  return {0, this->getNcol()};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Scalar, Trans _trans>
DenseMatrixStorage<_Scalar>& DenseMatrix<_Scalar, _trans>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Scalar, Trans _trans>
const DenseMatrixStorage<_Scalar>& DenseMatrix<_Scalar, _trans>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_
