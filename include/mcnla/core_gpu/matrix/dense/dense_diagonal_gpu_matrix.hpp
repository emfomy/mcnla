////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hpp
/// @brief   The dense diagonal GPU matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HPP_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HPP_

#include <mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hh>

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
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix(
    const index_t size
) noexcept
  : BaseType(size) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix(
    const index_t size,
    const index_t pitch
) noexcept
  : BaseType(size, pitch+1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix(
    const index_t size,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(size, pitch+1, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix(
    const index_t size,
    const index_t pitch,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(size, pitch+1, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>::DenseDiagonalGpuMatrix(
    const DenseDiagonalGpuMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>& DenseDiagonalGpuMatrix<_Val>::operator=(
    const DenseDiagonalGpuMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::size
///
template <typename _Val>
index_t DenseDiagonalGpuMatrix<_Val>::size() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::nnz
///
template <typename _Val>
index_t DenseDiagonalGpuMatrix<_Val>::nnz() const noexcept {
  return this->size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::pitch
///
template <typename _Val>
index_t DenseDiagonalGpuMatrix<_Val>::pitch() const noexcept {
  return this->stride()-1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::reconstruct
///
template <typename _Val> template <typename... Args>
void DenseDiagonalGpuMatrix<_Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseDiagonalGpuMatrix<_Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::t
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>& DenseDiagonalGpuMatrix<_Val>::t() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::t
///
template <typename _Val>
const DenseDiagonalGpuMatrix<_Val>& DenseDiagonalGpuMatrix<_Val>::t() const noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::viewVector
///
template <typename _Val>
DenseGpuVector<_Val>& DenseDiagonalGpuMatrix<_Val>::viewVector() noexcept {
  return static_cast<VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::viewVector
///
template <typename _Val>
const DenseGpuVector<_Val>& DenseDiagonalGpuMatrix<_Val>::viewVector() const noexcept {
  return static_cast<const VectorType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::vectorize
///
template <typename _Val>
DenseGpuVector<_Val>& DenseDiagonalGpuMatrix<_Val>::vectorize() noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::vectorize
///
template <typename _Val>
const DenseGpuVector<_Val>& DenseDiagonalGpuMatrix<_Val>::vectorize() const noexcept {
  return viewVector();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::nrowImpl
///
template <typename _Val>
index_t DenseDiagonalGpuMatrix<_Val>::nrowImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::ncolImpl
///
template <typename _Val>
index_t DenseDiagonalGpuMatrix<_Val>::ncolImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::base
///
template <typename _Val>
DenseVectorStorage<_Val, GpuArray>& DenseDiagonalGpuMatrix<_Val>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseDiagonalMatrix::base
///
template <typename _Val>
const DenseVectorStorage<_Val, GpuArray>& DenseDiagonalGpuMatrix<_Val>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HPP_
