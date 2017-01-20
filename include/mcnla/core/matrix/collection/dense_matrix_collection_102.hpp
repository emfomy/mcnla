////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_102.hpp
/// @brief   The the dense matrix collection with dimension order [1 0 2].
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
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102() noexcept
  : BaseType(),
    data_(),
    nrow_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : BaseType(),
    data_(nrow*nmat, ncol),
    nrow_(nrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : DenseMatrixCollection102(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102(
    const index_t nrow,
    const MatrixType &data
) noexcept
  : BaseType(),
    data_(data),
    nrow_(nrow) {
  mcnla_assert_ge(this->nrow(), 0);
  mcnla_assert_ge(this->ncol(), 0);
  mcnla_assert_ge(this->nmat(), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102(
    const DenseMatrixCollection102 &other
) noexcept
  : BaseType(other),
    data_(other.data_),
    nrow_(other.nrow_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>::DenseMatrixCollection102(
    DenseMatrixCollection102 &&other
) noexcept
  : BaseType(std::move(other)),
    data_(std::move(other.data_)),
    nrow_(other.nrow_) {
  other.nrow_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>& DenseMatrixCollection102<_Scalar>::operator=( const DenseMatrixCollection102 &other ) noexcept {
  BaseType::operator=(other);
  data_ = other.data_;
  nrow_ = other.nrow_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar>& DenseMatrixCollection102<_Scalar>::operator=( DenseMatrixCollection102 &&other ) noexcept {
  BaseType::operator=(std::move(other));
  data_ = std::move(other.data_);
  nrow_ = other.nrow_; other.nrow_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <class _Scalar>
bool DenseMatrixCollection102<_Scalar>::isShrunk() const noexcept {
  return (data_.nrow() % nrow_ == 0) && data_.isShrunk();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw data.
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar>& DenseMatrixCollection102<_Scalar>::data() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  data
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar>& DenseMatrixCollection102<_Scalar>::data() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the collection.
///
/// @attention  The data is also reallocated.
///
template <class _Scalar> template <typename... Args>
void DenseMatrixCollection102<_Scalar>::reconstruct(
    Args... args
) noexcept {
  *this = DenseMatrixCollection102<_Scalar>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const IdxRange &idxrange
) noexcept {
  return SetType(nrow_, data_(idxrange * nrow_, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Scalar>
const DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const IdxRange &idxrange
) const noexcept {
  return SetType(nrow_, data_(idxrange * nrow_, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) noexcept {
  return SetType(nrow_, data_(idxrange * nrow_, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const IdxRange& )
///
template <class _Scalar>
const DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const char*,
    const char*,
    const IdxRange &idxrange
) const noexcept {
  return SetType(nrow_, data_(idxrange * nrow_, ""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a collection of rows.
///
template <class _Scalar>
DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const char*,
    const IdxRange &colrange,
    const char*
) noexcept {
  return SetType(nrow_, data_("", colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const char*, const IdxRange&, const char* )
///
template <class _Scalar>
const DenseMatrixCollection102<_Scalar> DenseMatrixCollection102<_Scalar>::operator()(
    const char*,
    const IdxRange &colrange,
    const char*
) const noexcept {
  return SetType(nrow_, data_("", colrange));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfolds the collection.
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixCollection102<_Scalar>::unfold() noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixCollection102<_Scalar>::unfold() const noexcept {
  return data_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nrow
///
template <class _Scalar>
index_t DenseMatrixCollection102<_Scalar>::nrowImpl() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::ncol
///
template <class _Scalar>
index_t DenseMatrixCollection102<_Scalar>::ncolImpl() const noexcept {
  return data_.ncol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::nmat
///
template <class _Scalar>
index_t DenseMatrixCollection102<_Scalar>::nmatImpl() const noexcept {
  return nrow_ ? (data_.nrow() / nrow_) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Scalar>
DenseMatrixRowMajor<_Scalar> DenseMatrixCollection102<_Scalar>::getMatrixImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_(IdxRange{idx, (idx+1)} * nrow_, "");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixCollectionWrapper::operator()( const index_t )
///
template <class _Scalar>
const DenseMatrixRowMajor<_Scalar> DenseMatrixCollection102<_Scalar>::getMatrixImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->nmat());
  return data_(IdxRange{idx, (idx+1)} * nrow_, "");
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HPP_
