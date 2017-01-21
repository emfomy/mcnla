////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_storage.hpp
/// @brief   The dense matrix storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_

#include <mcnla/core/matrix/dense/dense_matrix_storage.hh>

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
DenseMatrixStorage<_Scalar>::DenseMatrixStorage() noexcept
  : BaseType(),
    dim0_(0),
    dim1_(0),
    pitch_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1
) noexcept
  : BaseType(dim0 * dim1),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(dim0) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch
) noexcept
  : BaseType(pitch * dim1),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
  mcnla_assert_ge(capacity, pitch_ * (dim1_-1) + dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(val >> offset),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
  mcnla_assert_ge(this->capacity(), pitch_ * (dim1_-1) + dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const DenseMatrixStorage &other
) noexcept
  : BaseType(other),
    dim0_(other.dim0_),
    dim1_(other.dim1_),
    pitch_(other.pitch_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
  DenseMatrixStorage &&other
) noexcept
  : BaseType(std::move(other)),
    dim0_(other.dim0_),
    dim1_(other.dim1_),
    pitch_(other.pitch_) {
  other.dim0_  = 0;
  other.dim1_  = 0;
  other.pitch_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>& DenseMatrixStorage<_Scalar>::operator=(
    const DenseMatrixStorage &other
) noexcept {
  BaseType::operator=(other);
  dim0_  = other.dim0_;
  dim1_  = other.dim1_;
  pitch_ = other.pitch_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>& DenseMatrixStorage<_Scalar>::operator=(
    DenseMatrixStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  dim0_  = other.dim0_;   other.dim0_  = 0;
  dim1_  = other.dim1_;   other.dim1_  = 0;
  pitch_ = other.pitch_;  other.pitch_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isShrunk() const noexcept {
  return (dim0_ == pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isSquare() const noexcept {
  return (dim0_ == dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the second dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::dim1() const noexcept {
  return dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0, dim1 ]
///
template <typename _Scalar>
std::tuple<index_t, index_t> DenseMatrixStorage<_Scalar>::dims() const noexcept {
  return std::make_tuple(dim0_, dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::pitch() const noexcept {
  return pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseMatrixStorage<_Scalar>::elemImpl(
    const index_t idx0,
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
  return this->valPtr()[posImpl(idx0, idx1)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  elemImpl
///
template <typename _Scalar>
const _Scalar& DenseMatrixStorage<_Scalar>::elemImpl(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
  return this->valPtr()[posImpl(idx0, idx1)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::posImpl(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  return idx0 + idx1 * pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the matrix.
///
/// @attention  The new space is kept but not initialized.
///
template <typename _Scalar>
void DenseMatrixStorage<_Scalar>::resizeImpl(
    const index_t dim0,
    const index_t dim1
) noexcept {
  mcnla_assert_ge(dim0, 0);
  mcnla_assert_ge(dim1, 0);
  mcnla_assert_ge(pitch_, dim0);
  mcnla_assert_ge(this->capacity(), pitch_ * (dim1-1) + dim0);
  dim0_ = dim0;
  dim1_ = dim1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar> DenseMatrixStorage<_Scalar>::getMatrixImpl(
    const IdxRange &range0,
    const IdxRange &range1
) noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  mcnla_assert_ge(range1.begin, 0); mcnla_assert_le(range1.end, dim1_); mcnla_assert_ge(range1.length(), 0);
  return MatrixStorageType(range0.length(), range1.length(), pitch_, val_, posImpl(range0.begin, range1.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getMatrixImpl
///
template <typename _Scalar>
const DenseMatrixStorage<_Scalar> DenseMatrixStorage<_Scalar>::getMatrixImpl(
    const IdxRange &range0,
    const IdxRange &range1
) const noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  mcnla_assert_ge(range1.begin, 0); mcnla_assert_le(range1.end, dim1_); mcnla_assert_ge(range1.length(), 0);
  return MatrixStorageType(range0.length(), range1.length(), pitch_, val_, posImpl(range0.begin, range1.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getVector0Impl(
    const IdxRange &range0,
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx1, 0, dim1_);
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  return VectorStorageType(range0.length(), 1, val_, posImpl(range0.begin, idx1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector0Impl
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getVector0Impl(
    const IdxRange &range0,
    const index_t idx1
) const noexcept {
  mcnla_assert_gelt(idx1, 0, dim1_);
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  return VectorStorageType(range0.length(), 1, val_, posImpl(range0.begin, idx1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector0Impl
///
template <typename _Scalar>
DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getVector1Impl(
    const index_t idx0,
    const IdxRange &range1
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_ge(range1.begin, 0); mcnla_assert_le(range1.end, dim1_); mcnla_assert_ge(range1.length(), 0);
  return VectorStorageType(range1.length(), pitch_, val_, posImpl(idx0, range1.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector0Impl
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getVector1Impl(
    const index_t idx0,
    const IdxRange &range1
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_ge(range1.begin, 0); mcnla_assert_le(range1.end, dim1_); mcnla_assert_ge(range1.length(), 0);
  return VectorStorageType(range1.length(), pitch_, val_, posImpl(idx0, range1.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
/// @note @a idx > 0 for above diagonals, @a idx < 0 for below diagonals.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getDiagonalImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gtlt(idx, -dim0_, dim1_);
  index_t length;
  index_t pos;
  if ( idx < 0 ) {
    pos = posImpl(-idx, 0);
    if ( dim0_ + idx > dim1_ && dim0_ > dim1_ ) {
      length = dim1_;
    } else {
      length = dim0_ + idx;
    }
  } else {
    pos = posImpl(0, idx);
    if ( dim1_ - idx > dim0_ && dim1_ > dim0_ ) {
      length = dim0_;
    } else {
      length = dim1_ - idx;
    }
  }
  return VectorStorageType(length, pitch_+1, val_, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonalImpl
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::getDiagonalImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gtlt(idx, -dim0_, dim1_);
  index_t length;
  index_t pos;
  if ( idx < 0 ) {
    pos = posImpl(-idx, 0);
    if ( dim0_ + idx > dim1_ && dim0_ > dim1_ ) {
      length = dim1_;
    } else {
      length = dim0_ + idx;
    }
  } else {
    pos = posImpl(0, idx);
    if ( dim1_ - idx > dim0_ && dim1_ > dim0_ ) {
      length = dim0_;
    } else {
      length = dim1_ - idx;
    }
  }
  return VectorStorageType(length, pitch_+1, val_, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Vectorize the matrix.
/// Returns a vector containing all elements between (0, 0) and (#dim0_-1, #dim1_-1) in the memory.
///
/// @note  The length of the output vector is #pitch_ &times; (#dim1_-1) + #dim0_.
///
/// @attention  The output vector contains the out-of-range spaces.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::vectorizeImpl() noexcept {
  return VectorStorageType(pitch_ * (dim1_-1) + dim0_, 1, val_, posImpl(0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorizeImpl
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar> DenseMatrixStorage<_Scalar>::vectorizeImpl() const noexcept {
  return VectorStorageType(pitch_ * (dim1_-1) + dim0_, 1, val_, posImpl(0, 0));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
