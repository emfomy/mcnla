////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_vector.hh
/// @brief   The definition of dense GPU vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_vector_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/kit/gpu_array.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class DenseGpuVector;
template <typename _Val> class DenseGpuDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector traits.
///
template <typename _Val>
struct Traits<matrix::DenseGpuVector<_Val>> {

  using ValType     = _Val;

  using RealType    = matrix::DenseGpuVector<RealValT<_Val>>;
  using ComplexType = matrix::DenseGpuVector<ComplexValT<_Val>>;

  using VectorType  = matrix::DenseGpuVector<_Val>;

  using DiagonalType = matrix::DenseGpuVector<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector instantiation type traits.
///
template <typename _Type>
struct IsDenseGpuVector : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseGpuVector
///
template <typename _Val>
struct IsDenseGpuVector<matrix::DenseGpuVector<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector assert.
///
#define assertDenseGpuVector( Type ) \
    static_assert(traits::IsDenseGpuVector<Type>::value, "'"#Type"' is not a dense GPU vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense GPU vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseGpuVector : public DenseVectorBase<_Val, DenseVector, DenseDiagonalMatrix, GpuArray> {

 private:

  using BaseType = DenseVectorBase<_Val, DenseVector, DenseDiagonalMatrix, GpuArray>;

 public:

  using BaseType::DenseVectorBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t idx ) noexcept = delete;
  inline void operator()( const index_t idx ) const noexcept = delete;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
