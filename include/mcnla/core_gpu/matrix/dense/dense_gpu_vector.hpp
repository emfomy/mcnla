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
  : BaseType(0, 1, GpuArray<_Val>()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const index_t length,
    const index_t stride
) noexcept
  : BaseType(length, stride, GpuArray<_Val>(length * stride)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const SizesType sizes,
    const index_t stride
) noexcept
  : DenseGpuVector(std::get<0>(sizes), stride) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const index_t length,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(length, stride, GpuArray<_Val>(capacity)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseGpuVector<_Val>::DenseGpuVector(
    const SizesType sizes,
    const index_t stride,
    const index_t capacity
) noexcept
  : DenseGpuVector(std::get<0>(sizes), stride, capacity) {}

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
  : BaseType(length, stride, val, offset) {}

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
/// @copydoc  mcnla::matrix::DenseVector::viewDiagonal
///
template <typename _Val>
DenseDiagonalGpuMatrix<_Val>& DenseGpuVector<_Val>::viewDiagonal() noexcept {
  return static_cast<DiagonalType&>(BaseType::viewDiagonal());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  viewDiagonal
///
template <typename _Val>
const DenseDiagonalGpuMatrix<_Val>& DenseGpuVector<_Val>::viewDiagonal() const noexcept {
  return static_cast<const DiagonalType&>(BaseType::viewDiagonal());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::operator()( const IdxRange& )
///
template <typename _Val>
DenseGpuVector<_Val> DenseGpuVector<_Val>::operator()(
    const IdxRange &range
) noexcept {
  return static_cast<VectorType&&>(BaseType::operator()(range));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::DenseVector::operator()( const IdxRange& )
///
template <typename _Val>
const DenseGpuVector<_Val> DenseGpuVector<_Val>::operator()(
    const IdxRange &range
) const noexcept {
  return static_cast<const VectorType&&>(BaseType::operator()(range));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HPP_
