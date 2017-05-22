////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_102.hpp
/// @brief   The the dense matrix collection with dimension order (dim1, dim0, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HPP_

#include <mcnla/core/matrix/collection/dense_matrix_collection_102.hh>

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
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection() noexcept
  : data_(),
    nrow_(0),
    mrow_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
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
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
    const SizesType sizes
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
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
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
    const SizesType sizes,
    const index_t mrow
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), mrow) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
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
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
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
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>::DenseMatrixCollection(
    const DenseMatrixCollection &other
) noexcept
  : data_(other.data_),
    nrow_(other.nrow_),
    mrow_(other.mrow_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val>& DenseMatrixCollection102Base<_Core, _Val>::operator=(
    const DenseMatrixCollection &other
) noexcept {
  data_ = other.data_;
  nrow_ = other.nrow_;
  mrow_ = other.mrow_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the collection.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::copy() const noexcept {
  return DenseMatrixCollection(nrow_, mrow_, data_.copy());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Core, typename _Val>
bool DenseMatrixCollection102Base<_Core, _Val>::isShrunk() const noexcept {
  return (nrow_ == mrow_) && (data_.pitch() % mrow_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of rows.
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection102Base<_Core, _Val>::mrow() const noexcept {
  return mrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::TRANS>& DenseMatrixCollection102Base<_Core, _Val>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::TRANS>& DenseMatrixCollection102Base<_Core, _Val>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <class _Core, typename _Val> template <typename... Args>
void DenseMatrixCollection102Base<_Core, _Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection102Base<_Core, _Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
const DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
const DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <class _Core, typename _Val>
DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const FullRange, const IdxRange&, const FullRange )
///
template <class _Core, typename _Val>
const DenseMatrixCollection102Base<_Core, _Val> DenseMatrixCollection102Base<_Core, _Val>::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::TRANS>& DenseMatrixCollection102Base<_Core, _Val>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::TRANS>& DenseMatrixCollection102Base<_Core, _Val>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::isEmpty
///
template <class _Core, typename _Val>
bool DenseMatrixCollection102Base<_Core, _Val>::isEmptyImpl() const noexcept {
  return data_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection102Base<_Core, _Val>::nrowImpl() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection102Base<_Core, _Val>::ncolImpl() const noexcept {
  return data_.ncol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection102Base<_Core, _Val>::nmatImpl() const noexcept {
  return mrow_ ? (data_.nrow() / mrow_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::TRANS> DenseMatrixCollection102Base<_Core, _Val>::getImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::TRANS> DenseMatrixCollection102Base<_Core, _Val>::getImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HPP_
