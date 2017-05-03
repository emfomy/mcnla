////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hh
/// @brief   The definition of definition of dense diagonal GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp>
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
struct Traits<matrix::DenseDiagonalGpuMatrix<_Val>> {

  using ValType     = _Val;
  using RealType    = matrix::DenseDiagonalGpuMatrix<RealValT<_Val>>;
  using ComplexType = matrix::DenseDiagonalGpuMatrix<ComplexValT<_Val>>;
  using VectorType  = matrix::DenseGpuVector<_Val>;
  using MatrixType  = matrix::DenseDiagonalGpuMatrix<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal GPU matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseDiagonalGpuMatrix
///
template <typename _Val>
struct IsDenseDiagonalGpuMatrix<matrix::DenseDiagonalGpuMatrix<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal GPU matrix assert.
///
#define assertDenseDiagonalGpuMatrix( Type ) \
    static_assert(traits::IsDenseDiagonalGpuMatrix<Type>::value, "'"#Type"' is not a dense diagonal GPU matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense diagonal GPU matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseDiagonalGpuMatrix : public DenseDiagonalMatrixBase<_Val, DenseTypes> {

 private:

  using BaseType = DenseDiagonalMatrixBase<_Val, DenseTypes>;

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

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_
