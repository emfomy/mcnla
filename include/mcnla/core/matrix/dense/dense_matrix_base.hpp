////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_base.hpp
/// @brief   The dense matrix base.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_matrix_base.hh>

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
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol)) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const SizesType sizes
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const SizesType sizes,
    const index_t pitch
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const SizesType sizes,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), pitch, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, Trans _trans, class _Types>
DenseMatrixBase<_Val, _trans, _Types>::DenseMatrixBase(
    const DerivedType &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::DerivedType& DenseMatrixBase<_Val, _trans, _Types>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::DerivedType DenseMatrixBase<_Val, _trans, _Types>::copy() const noexcept {
  return DenseMatrixBase(this->nrow(), this->ncol(), this->pitch(), this->val().copy(), this->offset());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans, class _Types>
_Val& DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  return this->elemImpl(toDim0(rowidx, colidx), toDim1(rowidx, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans, class _Types>
const _Val& DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return this->elemImpl(toDim0(rowidx, colidx), toDim1(rowidx, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::posImpl
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::pos(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return this->posImpl(toDim0(rowidx, colidx), toDim1(rowidx, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, Trans _trans, class _Types> template <typename... Args>
void DenseMatrixBase<_Val, _trans, _Types>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixBase<_Val, _trans, _Types>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans, class _Types>
void DenseMatrixBase<_Val, _trans, _Types>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  this->resizeImpl(toDim0(nrow, ncol), toDim1(nrow, ncol));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans, class _Types>
void DenseMatrixBase<_Val, _trans, _Types>::resize(
    const index_t nrow,
    const FullRange
) noexcept {
  this->resizeImpl(toDim0(nrow, this->ncol()), toDim1(nrow, this->ncol()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans, class _Types>
void DenseMatrixBase<_Val, _trans, _Types>::resize(
    const FullRange,
    const index_t ncol
) noexcept {
  this->resizeImpl(toDim0(this->nrow(), ncol), toDim1(this->nrow(), ncol));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::TransposeType& DenseMatrixBase<_Val, _trans, _Types>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::TransposeType& DenseMatrixBase<_Val, _trans, _Types>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate of the matrix.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::ConjugateType& DenseMatrixBase<_Val, _trans, _Types>::c() noexcept {
  return static_cast<ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  c
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::ConjugateType& DenseMatrixBase<_Val, _trans, _Types>::c() const noexcept {
  return static_cast<const ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::HermitianType& DenseMatrixBase<_Val, _trans, _Types>::h() noexcept {
  return static_cast<HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  h
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::HermitianType& DenseMatrixBase<_Val, _trans, _Types>::h() const noexcept {
  return static_cast<const HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the symmetric view of the matrix.
///
template <typename _Val, Trans _trans, class _Types> template <Uplo _uplo>
typename _Types::template SyMatT<_Val, _trans, _uplo>&
    DenseMatrixBase<_Val, _trans, _Types>::viewSymmetric() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewSymmetric
///
template <typename _Val, Trans _trans, class _Types> template <Uplo _uplo>
const typename _Types::template SyMatT<_Val, _trans, _uplo>&
    DenseMatrixBase<_Val, _trans, _Types>::viewSymmetric() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the triangular view of the matrix.
///
template <typename _Val, Trans _trans, class _Types> template <Uplo _uplo>
typename _Types::template TrMatT<_Val, _trans, _uplo>&
    DenseMatrixBase<_Val, _trans, _Types>::viewTriangular() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewTriangular
///
template <typename _Val, Trans _trans, class _Types> template <Uplo _uplo>
const typename _Types::template TrMatT<_Val, _trans, _uplo>&
    DenseMatrixBase<_Val, _trans, _Types>::viewTriangular() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::DiagonalType
    DenseMatrixBase<_Val, _trans, _Types>::viewDiagonal() noexcept {
  mcnla_assert_true(this->isSquare());
  return getDiagonal().viewDiagonal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::DiagonalType
    DenseMatrixBase<_Val, _trans, _Types>::viewDiagonal() const noexcept {
  return getDiagonal().viewDiagonal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const IdxRange &colrange
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colrange) : this->getMatrixImpl(colrange, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colrange) : this->getMatrixImpl(colrange, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const FullRange,
    const IdxRange &colrange
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowfullrange(), colrange) : this->getMatrixImpl(colrange, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const FullRange,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowfullrange(), colrange) : this->getMatrixImpl(colrange, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const FullRange
) noexcept {
  return static_cast<MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colfullrange()) : this->getMatrixImpl(colfullrange(), rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::MatrixType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const FullRange
) const noexcept {
  return static_cast<const MatrixType&&>(
      !isTrans(_trans) ? this->getMatrixImpl(rowrange, colfullrange()) : this->getMatrixImpl(colfullrange(), rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a column vector segment.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const index_t colidx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowrange, colidx) : this->getVector1Impl(colidx, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const index_t )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const IdxRange &rowrange,
    const index_t colidx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowrange, colidx) : this->getVector1Impl(colidx, rowrange)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const index_t )
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const FullRange,
    const index_t colidx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowfullrange(), colidx) : this->getVector1Impl(colidx, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const index_t )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const FullRange,
    const index_t colidx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector0Impl(rowfullrange(), colidx) : this->getVector1Impl(colidx, rowfullrange())
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a row vector segment.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const IdxRange &colrange
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colrange) : this->getVector0Impl(colrange, rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const index_t, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const IdxRange &colrange
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colrange) : this->getVector0Impl(colrange, rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const index_t, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const FullRange
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colfullrange()) : this->getVector0Impl(colfullrange(), rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const index_t, const IdxRange& )
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::operator()(
    const index_t rowidx,
    const FullRange
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colfullrange()) : this->getVector0Impl(colfullrange(), rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getDiagonalImpl
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::getDiagonal(
    const index_t idx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getDiagonalImpl(idx) : this->getDiagonalImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonal
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::getDiagonal(
    const index_t idx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getDiagonalImpl(idx) : this->getDiagonalImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::vectorizeImpl
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::vectorize() noexcept {
  return static_cast<VectorType&&>(this->vectorizeImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::VectorType DenseMatrixBase<_Val, _trans, _Types>::vectorize() const noexcept {
  return static_cast<const VectorType&&>(this->vectorizeImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::toDim0(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<0>(sizes) : std::get<1>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::toDim0(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? nrow : ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the second dimension from sizes.
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::toDim1(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<1>(sizes) : std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim1
///
template <typename _Val, Trans _trans, class _Types>
index_t DenseMatrixBase<_Val, _trans, _Types>::toDim1(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? ncol : nrow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full row index range.
///
template <typename _Val, Trans _trans, class _Types>
const IdxRange DenseMatrixBase<_Val, _trans, _Types>::rowfullrange() const noexcept {
  return {0_i, this->nrow()};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full column index range.
///
template <typename _Val, Trans _trans, class _Types>
const IdxRange DenseMatrixBase<_Val, _trans, _Types>::colfullrange() const noexcept {
  return {0_i, this->ncol()};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val, Trans _trans, class _Types>
typename DenseMatrixBase<_Val, _trans, _Types>::BaseType& DenseMatrixBase<_Val, _trans, _Types>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val, Trans _trans, class _Types>
const typename DenseMatrixBase<_Val, _trans, _Types>::BaseType& DenseMatrixBase<_Val, _trans, _Types>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HPP_
