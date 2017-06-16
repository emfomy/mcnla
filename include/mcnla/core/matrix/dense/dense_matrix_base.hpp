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
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol)) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const SizesType sizes
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const SizesType sizes,
    const index_t pitch
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const SizesType sizes,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
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
template <class _Core, typename _Val, Trans _trans>
DenseMatrixBase<_Core, _Val, _trans>::DenseMatrixBase(
    const DenseMatrixBase &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans>& DenseMatrixBase<_Core, _Val, _trans>::operator=(
    const DenseMatrixBase &other
) noexcept {
  BaseType::operator=(other);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::copy() const noexcept {
  DenseMatrixBase retval(this->nrow(), this->ncol(), this->pitch(), this->val().copy(), this->offset());
  return retval.derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <class _Core, typename _Val, Trans _trans>
_Val& DenseMatrixBase<_Core, _Val, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  return this->elemImpl(toDim0(rowidx, colidx), toDim1(rowidx, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::elemImpl
///
template <class _Core, typename _Val, Trans _trans>
const _Val& DenseMatrixBase<_Core, _Val, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return this->elemImpl(toDim0(rowidx, colidx), toDim1(rowidx, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::posImpl
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::pos(
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
template <class _Core, typename _Val, Trans _trans> template <typename ..._Args>
void DenseMatrixBase<_Core, _Val, _trans>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseMatrixBase<_Core, _Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <class _Core, typename _Val, Trans _trans>
void DenseMatrixBase<_Core, _Val, _trans>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  this->resizeImpl(toDim0(nrow, ncol), toDim1(nrow, ncol));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <class _Core, typename _Val, Trans _trans>
void DenseMatrixBase<_Core, _Val, _trans>::resize(
    const index_t nrow,
    const FullRange
) noexcept {
  this->resizeImpl(toDim0(nrow, this->ncol()), toDim1(nrow, this->ncol()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::resizeImpl
///
template <class _Core, typename _Val, Trans _trans>
void DenseMatrixBase<_Core, _Val, _trans>::resize(
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
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, changeTrans(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, changeTrans(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, changeConj(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::c() noexcept {
  return static_cast<ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  c
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, changeConj(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::c() const noexcept {
  return static_cast<const ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, changeHerm(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::h() noexcept {
  return static_cast<HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  h
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, changeHerm(_trans)>& DenseMatrixBase<_Core, _Val, _trans>::h() const noexcept {
  return static_cast<const HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the symmetric view of the matrix.
///
template <class _Core, typename _Val, Trans _trans> template <Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
SyMatS<_Core, DenseTag, _Val, _trans, _uplo>&
#else  // DOXYGEN_SHOULD_SKIP_THIS
typename DenseMatrixBase<_Core, _Val, _trans>::SymmetricType<_uplo>&
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    DenseMatrixBase<_Core, _Val, _trans>::sym() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  sym
///
template <class _Core, typename _Val, Trans _trans> template <Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
const SyMatS<_Core, DenseTag, _Val, _trans, _uplo>&
#else  // DOXYGEN_SHOULD_SKIP_THIS
const typename DenseMatrixBase<_Core, _Val, _trans>::SymmetricType<_uplo>&
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    DenseMatrixBase<_Core, _Val, _trans>::sym() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const SymmetricType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the upper symmetric view of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
SyMatS<_Core, DenseTag, _Val, _trans, Uplo::UPPER>& DenseMatrixBase<_Core, _Val, _trans>::symu() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<SymmetricType<Uplo::UPPER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  symu
///
template <class _Core, typename _Val, Trans _trans>
const SyMatS<_Core, DenseTag, _Val, _trans, Uplo::UPPER>& DenseMatrixBase<_Core, _Val, _trans>::symu() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const SymmetricType<Uplo::UPPER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the lower symmetric view of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
SyMatS<_Core, DenseTag, _Val, _trans, Uplo::LOWER>& DenseMatrixBase<_Core, _Val, _trans>::syml() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<SymmetricType<Uplo::LOWER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  syml
///
template <class _Core, typename _Val, Trans _trans>
const SyMatS<_Core, DenseTag, _Val, _trans, Uplo::LOWER>& DenseMatrixBase<_Core, _Val, _trans>::syml() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const SymmetricType<Uplo::LOWER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the triangular view of the matrix.
///
template <class _Core, typename _Val, Trans _trans> template <Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
TrMatS<_Core, DenseTag, _Val, _trans, _uplo>&
#else  // DOXYGEN_SHOULD_SKIP_THIS
typename DenseMatrixBase<_Core, _Val, _trans>::TriangularType<_uplo>&
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    DenseMatrixBase<_Core, _Val, _trans>::tri() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  tri
///
template <class _Core, typename _Val, Trans _trans> template <Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
const TrMatS<_Core, DenseTag, _Val, _trans, _uplo>&
#else  // DOXYGEN_SHOULD_SKIP_THIS
const typename DenseMatrixBase<_Core, _Val, _trans>::TriangularType<_uplo>&
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  DenseMatrixBase<_Core, _Val, _trans>::tri() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const TriangularType<_uplo>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the upper triangular view of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
TrMatS<_Core, DenseTag, _Val, _trans, Uplo::UPPER>& DenseMatrixBase<_Core, _Val, _trans>::triu() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<TriangularType<Uplo::UPPER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  triu
///
template <class _Core, typename _Val, Trans _trans>
const TrMatS<_Core, DenseTag, _Val, _trans, Uplo::UPPER>& DenseMatrixBase<_Core, _Val, _trans>::triu() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const TriangularType<Uplo::UPPER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the lower triangular view of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
TrMatS<_Core, DenseTag, _Val, _trans, Uplo::LOWER>& DenseMatrixBase<_Core, _Val, _trans>::tril() noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<TriangularType<Uplo::LOWER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  tril
///
template <class _Core, typename _Val, Trans _trans>
const TrMatS<_Core, DenseTag, _Val, _trans, Uplo::LOWER>& DenseMatrixBase<_Core, _Val, _trans>::tril() const noexcept {
  mcnla_assert_true(this->isSquare());
  return static_cast<const TriangularType<Uplo::LOWER>&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the diagonal view of the matrix.
///
template <class _Core, typename _Val, Trans _trans>
DiMatS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::diag() noexcept {
  mcnla_assert_true(this->isSquare());
  return getDiag().diag();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  diag
///
template <class _Core, typename _Val, Trans _trans>
const DiMatS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::diag() const noexcept {
  return getDiag().diag();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
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
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::operator()(
    const index_t rowidx,
    const FullRange
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getVector1Impl(rowidx, colfullrange()) : this->getVector0Impl(colfullrange(), rowidx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::getDiagImpl
///
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::getDiag(
    const index_t idx
) noexcept {
  return static_cast<VectorType&&>(
      !isTrans(_trans) ? this->getDiagImpl(idx) : this->getDiagImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiag
///
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::getDiag(
    const index_t idx
) const noexcept {
  return static_cast<const VectorType&&>(
      !isTrans(_trans) ? this->getDiagImpl(idx) : this->getDiagImpl(-idx)
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::vecImpl
///
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::vec() noexcept {
  return static_cast<VectorType&&>(this->vecImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vec
///
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::vec() const noexcept {
  return static_cast<const VectorType&&>(this->vecImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixStorage::unfoldImpl
///
template <class _Core, typename _Val, Trans _trans>
GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::unfold() noexcept {
  return static_cast<VectorType&&>(this->unfoldImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  expand
///
template <class _Core, typename _Val, Trans _trans>
const GeVecS<_Core, DenseTag, _Val> DenseMatrixBase<_Core, _Val, _trans>::unfold() const noexcept {
  return static_cast<const VectorType&&>(this->unfoldImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mrow
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::mrowImpl() const noexcept {
  return !isTrans(_trans) ? this->mdim0() : this->mdim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixWrapper::mcol
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::mcolImpl() const noexcept {
  return !isTrans(_trans) ? this->mdim1() : this->mdim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::toDim0(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<0>(sizes) : std::get<1>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::toDim0(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? nrow : ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the second dimension from sizes.
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::toDim1(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<1>(sizes) : std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim1
///
template <class _Core, typename _Val, Trans _trans>
index_t DenseMatrixBase<_Core, _Val, _trans>::toDim1(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? ncol : nrow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full row index range.
///
template <class _Core, typename _Val, Trans _trans>
const IdxRange DenseMatrixBase<_Core, _Val, _trans>::rowfullrange() const noexcept {
  return {0_i, this->nrow()};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a full column index range.
///
template <class _Core, typename _Val, Trans _trans>
const IdxRange DenseMatrixBase<_Core, _Val, _trans>::colfullrange() const noexcept {
  return {0_i, this->ncol()};
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HPP_
