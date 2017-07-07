////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense/dense_matrix_collection_row_block.hpp
/// @brief   The the dense matrix collection of row-blocks.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HPP_

#include <mcnla/core/matrix/collection/dense/dense_matrix_collection_row_block.hh>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP DenseMatrixCollectionRowBlockBase<_Val>
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
MCNLA_TMP::GeMatCollS() noexcept
  : data_(),
    nrow_(0),
    mrow_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : data_(nrow*nmat, ncol),
    nrow_(nrow),
    mrow_(nrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const SizesType sizes
) noexcept
  : GeMatCollS(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat,
    const index_t mrow
) noexcept
  : data_(mrow*nmat, ncol),
    nrow_(nrow),
    mrow_(mrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
  mcnla_assert_ge(mrow_, nrow_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const SizesType sizes,
    const index_t mrow
) noexcept
  : GeMatCollS(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), mrow) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const index_t nrow,
    const MatrixType &data
) noexcept
  : data_(data),
    nrow_(nrow),
    mrow_(nrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const index_t nrow,
    const index_t mrow,
    const MatrixType &data
) noexcept
  : data_(data),
    nrow_(nrow),
    mrow_(mrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
  mcnla_assert_ge(mrow_, nrow_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val, Trans _trans>
MCNLA_TMP::GeMatCollS(
    const CollectionType &other
) noexcept
  : data_(other.data_),
    nrow_(other.nrow_),
    mrow_(other.mrow_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val, Trans _trans>
GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans>& MCNLA_TMP::operator=(
    const CollectionType &other
) noexcept {
  data_ = other.data_;
  nrow_ = other.nrow_;
  mrow_ = other.mrow_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the collection.
///
template <class _Core, typename _Val, Trans _trans>
GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::copy() const noexcept {
  return GeMatCollS(nrow_, mrow_, data_.copy());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Core, typename _Val, Trans _trans>
bool MCNLA_TMP::isShrunk() const noexcept {
  return (nrow_ == mrow_) && (data_.pitch() % mrow_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of rows.
///
template <class _Core, typename _Val, Trans _trans>
index_t MCNLA_TMP::mrow() const noexcept {
  return mrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans>& MCNLA_TMP::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans>& MCNLA_TMP::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <class _Core, typename _Val, Trans _trans> template <typename ..._Args>
void MCNLA_TMP::reconstruct(
    _Args... args
) noexcept {
  *this = GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <class _Core, typename _Val, Trans _trans>
GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val, Trans _trans>
const GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val, Trans _trans>
GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val, Trans _trans>
const GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <class _Core, typename _Val, Trans _trans>
GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const FullRange, const IdxRange&, const FullRange )
///
template <class _Core, typename _Val, Trans _trans>
const GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans> MCNLA_TMP::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans>& MCNLA_TMP::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans>& MCNLA_TMP::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::isEmpty
///
template <class _Core, typename _Val, Trans _trans>
bool MCNLA_TMP::isEmptyImpl() const noexcept {
  return data_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <class _Core, typename _Val, Trans _trans>
index_t MCNLA_TMP::nrowImpl() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <class _Core, typename _Val, Trans _trans>
index_t MCNLA_TMP::ncolImpl() const noexcept {
  return data_.ncol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <class _Core, typename _Val, Trans _trans>
index_t MCNLA_TMP::nmatImpl() const noexcept {
  return mrow_ ? (data_.nrow() / mrow_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val, Trans _trans>
GeMatS<_Core, DenseTag, _Val, _trans> MCNLA_TMP::getImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val, Trans _trans>
const GeMatS<_Core, DenseTag, _Val, _trans> MCNLA_TMP::getImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HPP_
