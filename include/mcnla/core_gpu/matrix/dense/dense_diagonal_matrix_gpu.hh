////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_matrix_gpu.hh
/// @brief   The definition of definition of  GPU dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
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
struct Traits<matrix::DenseDiagonalMatrixGpu<_Val>> {

  using ValType     = _Val;

  using RealType    = matrix::DenseDiagonalMatrixGpu<RealValT<_Val>>;
  using ComplexType = matrix::DenseDiagonalMatrixGpu<ComplexValT<_Val>>;

  using VectorType  = matrix::DenseVectorGpu<_Val>;
  using MatrixType  = matrix::DenseDiagonalMatrixGpu<_Val>;
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
struct IsDenseDiagonalMatrixGpu<matrix::DenseDiagonalMatrixGpu<_Val>> : std::true_type {};

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
/// @ingroup  matrix_dense_gpu_module
/// The  GPU dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DiMatI<GpuTag, DenseTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseDiagonalMatrixGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseDiagonalMatrixBase<GpuTag, _Val> {

 private:

  using BaseType = DenseDiagonalMatrixBase<GpuTag, _Val>;

 public:

  using BaseType::DenseDiagonalMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
