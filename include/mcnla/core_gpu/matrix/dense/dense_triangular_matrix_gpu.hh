////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_triangular_matrix_gpu.hh
/// @brief   The definition of GPU triangular dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_vector_gpu.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_matrix_gpu.hpp>

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
struct Traits<matrix::TrMatI<CoreGpuTag, DenseTag, _Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::TrMatI<CoreGpuTag, DenseTag, RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::TrMatI<CoreGpuTag, DenseTag, ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::GeVecI<CoreGpuTag, DenseTag, _Val>;
  using MatrixType  = matrix::TrMatI<CoreGpuTag, DenseTag, _Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularMatrixGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseTriangularMatrixGpu
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularMatrixGpu<matrix::TrMatI<CoreGpuTag, DenseTag, _Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularMatrixGpu( Type ) \
    static_assert(traits::IsDenseTriangularMatrixGpu<Type>::value, "'"#Type"' is not a dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_gpu_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
class TrMatI<CoreGpuTag, DenseTag, _Val, _trans, _uplo> : public DenseTriangularMatrixBase<CoreGpuTag, _Val, _trans, _uplo> {

 private:

  using BaseType = DenseTriangularMatrixBase<CoreGpuTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseTriangularMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  matrix_gpu_dense_module
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
using DenseTriangularMatrixGpu = TrMatI<CoreGpuTag, DenseTag, _Val, _trans, _uplo>;

/// @ingroup  matrix_gpu_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixGpuColMajor = TrMatI<CoreGpuTag, DenseTag, _Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_gpu_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularMatrixGpuRowMajor = TrMatI<CoreGpuTag, DenseTag, _Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_
