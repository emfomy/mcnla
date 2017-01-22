////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_storage.hpp
/// @brief   The COO matrix storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HPP_

#include <mcnla/core/matrix/coo/coo_matrix_storage.hh>
#include <algorithm>

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
CooMatrixStorage<_Scalar>::CooMatrixStorage() noexcept
  : BaseType(),
    Base0Type(),
    Base1Type(),
    dim0_(0),
    dim1_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>::CooMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t nnz
) noexcept
  : BaseType(nnz, nnz),
    Base0Type(nnz),
    Base1Type(nnz),
    dim0_(dim0),
    dim1_(dim1) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>::CooMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(capacity, nnz),
    Base0Type(capacity),
    Base1Type(capacity),
    dim0_(dim0),
    dim1_(dim1) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(this->valCapacity(), nnz_);
  mcnla_assert_ge(this->idx0Capacity(), nnz_);
  mcnla_assert_ge(this->idx1Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>::CooMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t nnz,
    const ValArrayType &val,
    const IdxArrayType &idx0,
    const IdxArrayType &idx1,
    const index_t offset
) noexcept
  : BaseType(val >> offset, nnz),
    Base0Type(idx0 >> offset),
    Base1Type(idx1 >> offset),
    dim0_(dim0),
    dim1_(dim1) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(this->valCapacity(), nnz_);
  mcnla_assert_ge(this->idx0Capacity(), nnz_);
  mcnla_assert_ge(this->idx1Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>::CooMatrixStorage(
    const CooMatrixStorage &other
) noexcept
  : BaseType(other),
    Base0Type(other),
    Base1Type(other),
    dim0_(other.dim0_),
    dim1_(other.dim1_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>::CooMatrixStorage(
  CooMatrixStorage &&other
) noexcept
  : BaseType(std::move(other)),
    Base0Type(std::move(other)),
    Base1Type(std::move(other)),
    dim0_(other.dim0_),
    dim1_(other.dim1_) {
  other.dim0_ = 0;
  other.dim1_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>& CooMatrixStorage<_Scalar>::operator=(
    const CooMatrixStorage &other
) noexcept {
  BaseType::operator=(other);
  Base0Type::operator=(other);
  Base1Type::operator=(other);
  dim0_ = other.dim0_;
  dim1_ = other.dim1_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
CooMatrixStorage<_Scalar>& CooMatrixStorage<_Scalar>::operator=(
    CooMatrixStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  Base0Type::operator=(std::move(other));
  Base1Type::operator=(std::move(other));
  dim0_ = other.dim0_;  other.dim0_ = 0;
  dim1_ = other.dim1_;  other.dim1_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <typename _Scalar>
bool CooMatrixStorage<_Scalar>::isEmpty() const noexcept {
  return BaseType::isEmpty() && Base0Type::isEmpty() && Base1Type::isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Scalar>
bool CooMatrixStorage<_Scalar>::isSquare() const noexcept {
  return (dim0_ == dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Scalar>
index_t CooMatrixStorage<_Scalar>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the second dimension.
///
template <typename _Scalar>
index_t CooMatrixStorage<_Scalar>::dim1() const noexcept {
  return dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0, dim1 ]
///
template <typename _Scalar>
std::tuple<index_t, index_t> CooMatrixStorage<_Scalar>::dims() const noexcept {
  return std::make_tuple(dim0_, dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar CooMatrixStorage<_Scalar>::elemImpl(
    const index_t idx0,
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
  index_t pos = posImpl(idx0, idx1);
  return (pos >= 0) ? this->valPtr()[pos] : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  elemImpl
///
template <typename _Scalar>
const _Scalar CooMatrixStorage<_Scalar>::elemImpl(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
  index_t pos = posImpl(idx0, idx1);
  return (pos >= 0) ? this->valPtr()[pos] : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t CooMatrixStorage<_Scalar>::posImpl(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  index_t pos1 = std::find(idx1Ptr(), idx1Ptr() + nnz_, idx1) - idx1Ptr();
  if ( pos1 == nnz_ ) {
    return -1;
  }
  index_t pos1n = std::find_if_not(idx1Ptr() + pos1, idx1Ptr() + nnz_,
      [=]( const index_t idx ) { return idx == idx1; }
  ) - idx1Ptr();
  index_t pos0 = std::find(idx0Ptr() + pos1, idx0Ptr() + pos1n, idx0) - idx0Ptr();
  return (pos0 < pos1n) ? pos0 : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position and nonzero elements of given index range.
///
template <typename _Scalar>
void CooMatrixStorage<_Scalar>::posImpl(
    const index_t idx1,
          index_t &pos,
          index_t &nnz
) const noexcept {
  pos = std::lower_bound(idx1Ptr(), idx1Ptr() + nnz_, idx1) - idx1Ptr();
  nnz = std::lower_bound(idx1Ptr() + pos, idx1Ptr() + nnz_, idx1+1) - idx1Ptr() - pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the matrix.
///
/// @attention  The new space is kept but not initialized.
///
template <typename _Scalar>
void CooMatrixStorage<_Scalar>::resizeImpl(
    const index_t dim0,
    const index_t dim1,
    const index_t nnz
) noexcept {
  mcnla_assert_ge(dim0, 0);
  mcnla_assert_ge(dim1, 0);
  mcnla_assert_ge(this->valCapacity(), nnz);
  mcnla_assert_ge(this->idx0Capacity(), nnz);
  mcnla_assert_ge(this->idx1Capacity(), nnz);
  dim0_ = dim0;
  dim1_ = dim1;
  nnz_  = nnz;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar>
CooVectorStorage<_Scalar> CooMatrixStorage<_Scalar>::getVector0Impl(
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx1, 0, dim1_);
  index_t pos, nnz;
  posImpl(idx1, pos, nnz);
  return VectorStorageType(dim0_, nnz, val_, this->idx0(), pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector0Impl
///
template <typename _Scalar>
const CooVectorStorage<_Scalar> CooMatrixStorage<_Scalar>::getVector0Impl(
    const index_t idx1
) const noexcept {
  mcnla_assert_gelt(idx1, 0, dim1_);
  index_t pos, nnz;
  posImpl(idx1, pos, nnz);
  return VectorStorageType(dim0_, nnz, val_, this->idx0(), pos);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HPP_
