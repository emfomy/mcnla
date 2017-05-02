////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp
/// @brief   The dense GPU vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HPP_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HPP_

#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hh>

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
DenseGpuVector<_Val>::DenseGpuVector() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const index_t length,
    const index_t stride
) noexcept
  : BaseType(toDim0(length), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const SizesType sizes,
    const index_t stride
) noexcept
  : BaseType(toDim0(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(length), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), stride, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const index_t length,
    const index_t stride,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(toDim0(length), stride, val, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector( const DenseGpuVector &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseGpuVector<_Val>& DenseGpuVector<_Val>::operator=(
    const DenseGpuVector &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::nnz
///
template <typename _Val>
index_t DenseGpuVector<_Val>::nnz() const noexcept {
  return this->nelem();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::pos
///
template <typename _Val>
index_t DenseGpuVector<_Val>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::reconstruct
///
template <typename _Val> template <typename... Args>
void DenseGpuVector<_Val>::reconstruct(
    Args... args
) noexcept {
  *this = DenseGpuVector<_Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::resize
///
template <typename _Val>
void DenseGpuVector<_Val>::resize(
    const index_t length
) noexcept {
  this->resizeImpl(length, this->stride());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::resize
///
template <typename _Val>
void DenseGpuVector<_Val>::resize(
    const index_t length,
    const index_t stride
) noexcept {
  this->resizeImpl(length, stride);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::viewDiagonal
///
template <typename _Val>
DenseGpuDiagonalMatrix<_Val>& DenseGpuVector<_Val>::viewDiagonal() noexcept {
  return static_cast<DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::viewDiagonal
///
template <typename _Val>
const DenseGpuDiagonalMatrix<_Val>& DenseGpuVector<_Val>::viewDiagonal() const noexcept {
  return static_cast<const DiagonalType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::operator()( const IdxRange& )
///
template <typename _Val>
DenseGpuVector<_Val> DenseGpuVector<_Val>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::operator()( const IdxRange& )
///
template <typename _Val>
const DenseGpuVector<_Val> DenseGpuVector<_Val>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(this->getVectorImpl(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::lengthImpl
///
template <typename _Val>
index_t DenseGpuVector<_Val>::lengthImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::toDim0
///
template <typename _Val>
index_t DenseGpuVector<_Val>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::toDim0
///
template <typename _Val>
index_t DenseGpuVector<_Val>::toDim0(
    const index_t length
) const noexcept {
  return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::base
///
template <typename _Val>
DenseVectorStorage<_Val, GpuArray>& DenseGpuVector<_Val>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::base
///
template <typename _Val>
const DenseVectorStorage<_Val, GpuArray>& DenseGpuVector<_Val>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HPP_
