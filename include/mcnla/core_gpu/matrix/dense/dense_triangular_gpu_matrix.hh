////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_triangular_gpu_matrix.hh
/// @brief   The definition of dense triangular GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseTriangularGpuMatrix<_Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::DenseTriangularGpuMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::DenseTriangularGpuMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseTriangularGpuMatrix<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseTriangularGpuMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularGpuMatrix<matrix::DenseTriangularGpuMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularGpuMatrix( Type ) \
    static_assert(traits::IsDenseTriangularGpuMatrix<Type>::value, "'"#Type"' is not a dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
class DenseTriangularGpuMatrix : public DenseTriangularMatrixBase<_Val, _trans, _uplo, DenseGpuTypes> {

 private:

  using BaseType = DenseTriangularMatrixBase<_Val, _trans, _uplo, DenseGpuTypes>;

 public:

  using BaseType::DenseTriangularMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularGpuMatrixColMajor = DenseTriangularGpuMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularGpuMatrixRowMajor = DenseTriangularGpuMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_GPU_MATRIX_HH_
