////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_vector_gpu.hh
/// @brief   The definition of GPU dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_vector_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_matrix_gpu.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU dense vector traits.
///
template <typename _Val>
struct Traits<matrix::GeVecI<GpuTag, DenseTag, _Val>> {

  using ValType     = _Val;

  using RealType    = matrix::GeVecI<GpuTag, DenseTag, RealValT<_Val>>;
  using ComplexType = matrix::GeVecI<GpuTag, DenseTag, ComplexValT<_Val>>;

  using VectorType  = matrix::GeVecI<GpuTag, DenseTag, _Val>;

  using DiagonalType = matrix::DiMatI<GpuTag, DenseTag, _Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU dense vector instantiation type traits.
///
template <typename _Type>
struct IsDenseVectorGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseVectorGpu
///
template <typename _Val>
struct IsDenseVectorGpu<matrix::GeVecI<GpuTag, DenseTag, _Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU dense vector assert.
///
#define assertDenseVectorGpu( Type ) \
    static_assert(traits::IsDenseVectorGpu<Type>::value, "'"#Type"' is not a GPU dense vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_gpu_module
/// The GPU dense vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class GeVecI<GpuTag, DenseTag, _Val> : public DenseVectorBase<GpuTag, _Val> {

 private:

  using BaseType = DenseVectorBase<GpuTag, _Val>;

 public:

  using BaseType::DenseVectorBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t idx ) noexcept = delete;
  inline void operator()( const index_t idx ) const noexcept = delete;

};

/// @ingroup  matrix_dense_gpu_module
template <typename _Val>
using DenseVectorGpu = GeVecI<GpuTag, DenseTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_
