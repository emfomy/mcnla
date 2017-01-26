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
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120() noexcept
  : BaseType(),
    data_(),
    ncol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120(
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
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : DenseMatrixCollection120(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120(
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
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120(
    const DenseMatrixCollection120 &other
) noexcept
  : BaseType(other),
    data_(other.data_),
    ncol_(other.ncol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>::DenseMatrixCollection120(
    DenseMatrixCollection120 &&other
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
DenseMatrixCollection120<_Scalar>& DenseMatrixCollection120<_Scalar>::operator=( const DenseMatrixCollection120 &other ) noexcept {
  BaseType::operator=(other);
  data_ = other.data_;
  ncol_ = other.ncol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>& DenseMatrixCollection120<_Scalar>::operator=( DenseMatrixCollection120 &&other ) noexcept {
  BaseType::operator=(std::move(other));
  data_ = std::move(other.data_);
  ncol_ = other.ncol_; other.ncol_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseMatrixCollection120<_Scalar>::isShrunk() const noexcept {
  return (data_.ncol() % ncol_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar>& DenseMatrixCollection120<_Scalar>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar>& DenseMatrixCollection120<_Scalar>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <typename _Scalar> template <typename... Args>
void DenseMatrixCollection120<_Scalar>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection120<_Scalar>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a subcollection.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const IdxRange &idxrange
) noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
const DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <typename _Scalar>
const DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) const noexcept {
  return SetType(ncol_, data_("", idxrange * ncol_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) noexcept {
  return SetType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange&, const char*, const char* )
///
template <typename _Scalar>
const DenseMatrixCollection120<_Scalar> DenseMatrixCollection120<_Scalar>::operator()(
    const IdxRange &rowrange,
    const char*,
    const char*
) const noexcept {
  return SetType(ncol_, data_(rowrange, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixCollection120<_Scalar>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixCollection120<_Scalar>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixCollectionWrapper::nrow
///
template <typename _Scalar>
index_t DenseMatrixCollection120<_Scalar>::nrowImpl() const noexcept {
  return data_.nrow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixCollectionWrapper::ncol
///
template <typename _Scalar>
index_t DenseMatrixCollection120<_Scalar>::ncolImpl() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixCollectionWrapper::nmat
///
template <typename _Scalar>
index_t DenseMatrixCollection120<_Scalar>::nmatImpl() const noexcept {
  return ncol_ ? (data_.ncol() / ncol_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixCollection120<_Scalar>::getMatrixImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", IdxRange{idx, (idx+1)} * ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseMatrixCollectionWrapper::operator()( const index_t )
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixCollection120<_Scalar>::getMatrixImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_("", IdxRange{idx, (idx+1)} * ncol_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_120_HPP_
