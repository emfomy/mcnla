////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_matrix.hh
/// @brief   The definition of definition of dense GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_symmetric_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_triangular_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hpp>
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
/// The dense GPU matrix traits.
///
template <typename _Val, Trans _trans>
struct Traits<matrix::DenseGpuMatrix<_Val, _trans>> {

  static constexpr Trans trans = _trans;

  using ValType     = _Val;

  using RealType    = matrix::DenseGpuMatrix<RealValT<_Val>, _trans>;
  using ComplexType = matrix::DenseGpuMatrix<ComplexValT<_Val>, _trans>;

  using VectorType  = matrix::DenseGpuVector<_Val>;
  using MatrixType  = matrix::DenseGpuMatrix<_Val, _trans>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseGpuMatrix
///
template <typename _Val, Trans _trans>
struct IsDenseGpuMatrix<matrix::DenseGpuMatrix<_Val, _trans>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU matrix assert.
///
#define assertDenseGpuMatrix( Type ) \
    static_assert(traits::IsDenseGpuMatrix<Type>::value, "'"#Type"' is not a dense GPU matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense GPU matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL>
class DenseGpuMatrix : public DenseMatrixBase<_Val, _trans, DenseGpuTypes> {

 private:

  using BaseType = DenseMatrixBase<_Val, _trans, DenseGpuTypes>;

 public:

  using BaseType::DenseMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  gpu_matrix_dense_module
template <typename _Val>
using DenseGpuMatrixColMajor = DenseGpuMatrix<_Val, Trans::NORMAL>;

/// @ingroup  gpu_matrix_dense_module
template <typename _Val>
using DenseGpuMatrixRowMajor = DenseGpuMatrix<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_
