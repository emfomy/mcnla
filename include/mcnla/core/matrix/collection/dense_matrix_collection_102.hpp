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
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection() noexcept
  : data_(),
    nrow_(0),
    mrow_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
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
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
    const SizesType sizes
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
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
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
    const SizesType sizes,
    const index_t mrow
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), mrow) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
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
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
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
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
    const DenseMatrixCollection &other
) noexcept
  : data_(other.data_),
    nrow_(other.nrow_),
    mrow_(other.mrow_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val>
DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::DenseMatrixCollection(
    DenseMatrixCollection &&other
) noexcept
  : data_(std::move(other.data_)),
    nrow_(other.nrow_),
    mrow_(other.mrow_) {
  other.nrow_ = 0;
  other.mrow_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseMatrixCollection102<_Val>& DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator=(
    const DenseMatrixCollection &other
) noexcept {
  data_ = other.data_;
  nrow_ = other.nrow_;
  mrow_ = other.mrow_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val>
DenseMatrixCollection102<_Val>& DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator=(
    DenseMatrixCollection &&other
) noexcept {
  data_ = std::move(other.data_);
  nrow_ = other.nrow_; other.nrow_ = 0;
  mrow_ = other.mrow_; other.mrow_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Val>
bool DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::isShrunk() const noexcept {
  return (nrow_ == mrow_) && (data_.pitch() % mrow_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of rows.
///
template <typename _Val>
index_t DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::mrow() const noexcept {
  return mrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <typename _Val>
DenseMatrixRowMajor<_Val>&
    DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>&
    DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <typename _Val> template <typename... Args>
void DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <typename _Val>
DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Val>
const DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Val>
DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Val>
const DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(idxrange * mrow_, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <typename _Val>
DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const FullRange, const IdxRange&, const FullRange )
///
template <typename _Val>
const DenseMatrixCollection102<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::operator()(
    const FullRange,
    const IdxRange &colrange,
    const FullRange
) const noexcept {
  return CollectionType(nrow_, mrow_, data_(""_, colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <typename _Val>
DenseMatrixRowMajor<_Val>&
    DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>&
    DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::isEmpty
///
template <typename _Val>
bool DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::isEmptyImpl() const noexcept {
  return data_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <typename _Val>
index_t DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::nrowImpl() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <typename _Val>
index_t DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::ncolImpl() const noexcept {
  return data_.ncol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <typename _Val>
index_t DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::nmatImpl() const noexcept {
  return mrow_ ? ((data_.nrow() + mrow_ - nrow_) / mrow_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Val>
DenseMatrixRowMajor<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::getImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Val>
const DenseMatrixRowMajor<_Val> DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>::getImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_({idx*mrow_, idx*mrow_ + nrow_}, ""_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HPP_
