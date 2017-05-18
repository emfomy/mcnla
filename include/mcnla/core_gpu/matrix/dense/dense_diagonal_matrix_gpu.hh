////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_matrix_gpu.hh
/// @brief   The definition of definition of  GPU dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_vector_gpu.hpp>
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
/// The dense diagonal GPU matrix traits.
///
template <typename _Val>
struct Traits<matrix::DiMatI<CoreGpuTag, DenseTag, _Val>> {

  using ValType     = _Val;

  using RealType    = matrix::DiMatI<CoreGpuTag, DenseTag, RealValT<_Val>>;
  using ComplexType = matrix::DiMatI<CoreGpuTag, DenseTag, ComplexValT<_Val>>;

  using VectorType  = matrix::GeVecI<CoreGpuTag, DenseTag, _Val>;
  using MatrixType  = matrix::DiMatI<CoreGpuTag, DenseTag, _Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal GPU matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalMatrixGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseDiagonalMatrixGpu
///
template <typename _Val>
struct IsDenseDiagonalMatrixGpu<matrix::DiMatI<CoreGpuTag, DenseTag, _Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal GPU matrix assert.
///
#define assertDenseDiagonalMatrixGpu( Type ) \
    static_assert(traits::IsDenseDiagonalMatrixGpu<Type>::value, "'"#Type"' is not a dense diagonal GPU matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_gpu_dense_module
/// The  GPU dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DiMatI<CoreGpuTag, DenseTag, _Val> : public DenseDiagonalMatrixBase<CoreGpuTag, _Val> {

 private:

  using BaseType = DenseDiagonalMatrixBase<CoreGpuTag, _Val>;

 public:

  using BaseType::DenseDiagonalMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  matrix_gpu_dense_module
template <typename _Val>
using DenseDiagonalMatrixGpu = DiMatI<CoreGpuTag, DenseTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
