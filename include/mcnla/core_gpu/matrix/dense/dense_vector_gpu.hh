////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_vector_gpu.hh
/// @brief   The definition of GPU dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
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
/// The GPU dense vector instantiation type traits.
///
template <typename _Type>
struct IsDenseVectorGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseVectorGpu
///
template <typename _Val>
struct IsDenseVectorGpu<matrix::DenseVectorGpu<_Val>> : std::true_type {};

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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class GeVecS<GpuTag, DenseTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseVectorGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseVectorBase<GpuTag, _Val> {

 private:

  using BaseType = DenseVectorBase<GpuTag, _Val>;

 public:

  using BaseType::DenseVectorBase;
  using BaseType::operator();

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseVectorBase::operator=
  DenseVectorGpu& operator=( const DenseVectorGpu &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Gets element
  inline void operator()( const index_t idx ) noexcept = delete;
  inline void operator()( const index_t idx ) const noexcept = delete;

  // Copy
  inline void copy() const noexcept = delete;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_VECTOR_GPU_HH_
