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
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage() noexcept
  : BaseType(),
    dim0_(0),
    dim1_(0),
    pitch_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage(
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
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage(
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
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage(
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
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage(
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
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>::DenseMatrixStorage(
    const DenseMatrixStorage &other
) noexcept
  : BaseType(other),
    dim0_(other.dim0_),
    dim1_(other.dim1_),
    pitch_(other.pitch_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array>& DenseMatrixStorage<_Val, _Array>::operator=(
    const DenseMatrixStorage &other
) noexcept {
  BaseType::operator=(other);
  dim0_  = other.dim0_;
  dim1_  = other.dim1_;
  pitch_ = other.pitch_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Val, template <typename> class _Array>
bool DenseMatrixStorage<_Val, _Array>::isShrunk() const noexcept {
  return (dim0_ == pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Val, template <typename> class _Array>
bool DenseMatrixStorage<_Val, _Array>::isSquare() const noexcept {
  return (dim0_ == dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Val, template <typename> class _Array>
index_t DenseMatrixStorage<_Val, _Array>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the second dimension.
///
template <typename _Val, template <typename> class _Array>
index_t DenseMatrixStorage<_Val, _Array>::dim1() const noexcept {
  return dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0, dim1 ]
///
template <typename _Val, template <typename> class _Array>
std::tuple<index_t, index_t> DenseMatrixStorage<_Val, _Array>::dims() const noexcept {
  return std::make_tuple(dim0_, dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <typename _Val, template <typename> class _Array>
index_t DenseMatrixStorage<_Val, _Array>::pitch() const noexcept {
  return pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Val, template <typename> class _Array>
_Val& DenseMatrixStorage<_Val, _Array>::elemImpl(
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
template <typename _Val, template <typename> class _Array>
const _Val& DenseMatrixStorage<_Val, _Array>::elemImpl(
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
template <typename _Val, template <typename> class _Array>
index_t DenseMatrixStorage<_Val, _Array>::posImpl(
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
template <typename _Val, template <typename> class _Array>
void DenseMatrixStorage<_Val, _Array>::resizeImpl(
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
template <typename _Val, template <typename> class _Array>
DenseMatrixStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getMatrixImpl(
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
template <typename _Val, template <typename> class _Array>
const DenseMatrixStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getMatrixImpl(
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
template <typename _Val, template <typename> class _Array>
DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getVector0Impl(
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
template <typename _Val, template <typename> class _Array>
const DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getVector0Impl(
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
template <typename _Val, template <typename> class _Array>
DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getVector1Impl(
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
template <typename _Val, template <typename> class _Array>
const DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getVector1Impl(
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
template <typename _Val, template <typename> class _Array>
DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getDiagonalImpl(
    const index_t idx
) noexcept {
  mcnla_assert_gtlt(idx, -dim0_, dim1_);
  index_t length;
  index_t pos;
  if ( idx < 0 ) {
    pos = posImpl(-idx, 0_i);
    if ( dim0_ + idx > dim1_ && dim0_ > dim1_ ) {
      length = dim1_;
    } else {
      length = dim0_ + idx;
    }
  } else {
    pos = posImpl(0_i, idx);
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
template <typename _Val, template <typename> class _Array>
const DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::getDiagonalImpl(
    const index_t idx
) const noexcept {
  mcnla_assert_gtlt(idx, -dim0_, dim1_);
  index_t length;
  index_t pos;
  if ( idx < 0 ) {
    pos = posImpl(-idx, 0_i);
    if ( dim0_ + idx > dim1_ && dim0_ > dim1_ ) {
      length = dim1_;
    } else {
      length = dim0_ + idx;
    }
  } else {
    pos = posImpl(0_i, idx);
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
template <typename _Val, template <typename> class _Array>
DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::vectorizeImpl() noexcept {
  return VectorStorageType(pitch_ * (dim1_-1) + dim0_, 1, val_, posImpl(0_i, 0_i));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorizeImpl
///
template <typename _Val, template <typename> class _Array>
const DenseVectorStorage<_Val, _Array> DenseMatrixStorage<_Val, _Array>::vectorizeImpl() const noexcept {
  return VectorStorageType(pitch_ * (dim1_-1) + dim0_, 1, val_, posImpl(0_i, 0_i));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
