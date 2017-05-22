////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_012.hpp
/// @brief   The the dense matrix collection with dimension order (dim0, dim1, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HPP_

#include <mcnla/core/matrix/collection/dense_matrix_collection_012.hh>

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
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection() noexcept
  : data_(),
    ncol_(0),
    mcol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : data_(nrow, ncol*nmat),
    ncol_(ncol),
    mcol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const SizesType sizes
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat,
    const index_t mcol
) noexcept
  : data_(nrow, mcol*nmat),
    ncol_(ncol),
    mcol_(mcol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
  mcnla_assert_ge(mcol_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const SizesType sizes,
    const index_t mcol
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), mcol) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const index_t ncol,
    const MatrixType &data
) noexcept
  : data_(data),
    ncol_(ncol),
    mcol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const index_t ncol,
    const index_t mcol,
    const MatrixType &data
) noexcept
  : data_(data),
    ncol_(ncol),
    mcol_(mcol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
  mcnla_assert_ge(mcol_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>::DenseMatrixCollection(
    const DenseMatrixCollection &other
) noexcept
  : data_(other.data_),
    ncol_(other.ncol_),
    mcol_(other.mcol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val>& DenseMatrixCollection012Base<_Core, _Val>::operator=(
    const DenseMatrixCollection &other
) noexcept {
  data_ = other.data_;
  ncol_ = other.ncol_;
  mcol_ = other.mcol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the collection.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::copy() const noexcept {
  return DenseMatrixCollection(ncol_, mcol_, data_.copy());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Core, typename _Val>
bool DenseMatrixCollection012Base<_Core, _Val>::isShrunk() const noexcept {
  return (ncol_ == mcol_) && (data_.pitch() % mcol_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of columns.
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection012Base<_Core, _Val>::mcol() const noexcept {
  return mcol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::NORMAL>& DenseMatrixCollection012Base<_Core, _Val>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::NORMAL>& DenseMatrixCollection012Base<_Core, _Val>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <class _Core, typename _Val> template <typename... Args>
void DenseMatrixCollection012Base<_Core, _Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection012Base<_Core, _Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const IdxRange &idxrange
) noexcept {
  return CollectionType(ncol_, mcol_, data_(""_, idxrange * mcol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
const DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(ncol_, mcol_, data_(""_, idxrange * mcol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) noexcept {
  return CollectionType(ncol_, mcol_, data_(""_, idxrange * mcol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Core, typename _Val>
const DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const FullRange,
    const FullRange,
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(ncol_, mcol_, data_(""_, idxrange * mcol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <class _Core, typename _Val>
DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const IdxRange &rowrange,
    const FullRange,
    const FullRange
) noexcept {
  return CollectionType(ncol_, mcol_, data_(rowrange, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const FullRange, const FullRange )
///
template <class _Core, typename _Val>
const DenseMatrixCollection012Base<_Core, _Val> DenseMatrixCollection012Base<_Core, _Val>::operator()(
    const IdxRange &rowrange,
    const FullRange,
    const FullRange
) const noexcept {
  return CollectionType(ncol_, mcol_, data_(rowrange, ""_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::NORMAL>& DenseMatrixCollection012Base<_Core, _Val>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::NORMAL>& DenseMatrixCollection012Base<_Core, _Val>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::isEmpty
///
template <class _Core, typename _Val>
bool DenseMatrixCollection012Base<_Core, _Val>::isEmptyImpl() const noexcept {
  return data_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection012Base<_Core, _Val>::nrowImpl() const noexcept {
  return data_.nrow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection012Base<_Core, _Val>::ncolImpl() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <class _Core, typename _Val>
index_t DenseMatrixCollection012Base<_Core, _Val>::nmatImpl() const noexcept {
  return mcol_ ? (data_.ncol() / mcol_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val>
GeMatS<_Core, DenseTag, _Val, Trans::NORMAL> DenseMatrixCollection012Base<_Core, _Val>::getImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_(""_, {idx*mcol_, idx*mcol_ + ncol_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Core, typename _Val>
const GeMatS<_Core, DenseTag, _Val, Trans::NORMAL> DenseMatrixCollection012Base<_Core, _Val>::getImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_(""_, {idx*mcol_, idx*mcol_ + ncol_});
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HPP_
