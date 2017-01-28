////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_120.hpp
/// @brief   The the dense matrix collection with dimension order [1 2 0].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_120_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_120_HPP_

#include <mcnla/core/matrix/collection/dense_matrix_collection_120.hh>

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
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection() noexcept
  : BaseType(),
    data_(),
    ncol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : BaseType(),
    data_(nrow, ncol*nmat),
    ncol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : DenseMatrixCollection(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection(
    const index_t ncol,
    const MatrixType &data
) noexcept
  : BaseType(),
    data_(data),
    ncol_(ncol) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection(
    const DenseMatrixCollection &other
) noexcept
  : BaseType(other),
    data_(other.data_),
    ncol_(other.ncol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::DenseMatrixCollection(
    DenseMatrixCollection &&other
) noexcept
  : BaseType(std::move(other)),
    data_(std::move(other.data_)),
    ncol_(other.ncol_) {
  other.ncol_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>&
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator=(
    const DenseMatrixCollection &other
) noexcept {
  BaseType::operator=(other);
  data_ = other.data_;
  ncol_ = other.ncol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>&
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator=(
    DenseMatrixCollection &&other
) noexcept {
  BaseType::operator=(std::move(other));
  data_ = std::move(other.data_);
  ncol_ = other.ncol_; other.ncol_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::isShrunk() const noexcept {
  return (data_.ncol() % ncol_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar>&
    DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar>&
    DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <typename _Scalar> template <typename... Args>
void DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>(
                                                                                      args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const IdxRange &idxrange
) noexcept {
  return CollectionType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
const DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) noexcept {
  return CollectionType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
const DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) const noexcept {
  return CollectionType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <typename _Scalar>
DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) noexcept {
  return CollectionType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const char*, const char* )
///
template <typename _Scalar>
const DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>
  DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) const noexcept {
  return CollectionType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar>
    DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar>
    DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <typename _Scalar>
index_t DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::nrowImpl() const noexcept {
  return data_.nrow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <typename _Scalar>
index_t DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::ncolImpl() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <typename _Scalar>
index_t DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::nmatImpl() const noexcept {
  return ncol_ ? (data_.ncol() / ncol_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::getMatrixImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", IdxRange{idx, (idx+1)} * ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixCollection<DenseMatrixCollection120Tag, _Scalar, Trans::TRANS>::getMatrixImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", IdxRange{idx, (idx+1)} * ncol_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_120_HPP_
