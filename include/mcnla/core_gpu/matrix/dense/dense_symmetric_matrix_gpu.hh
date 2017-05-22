////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_symmetric_matrix_gpu.hh
/// @brief   The definition of GPU symmetric dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix_base.hpp>
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
/// The dense symmetric matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseSymmetricMatrixGpu<_Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::DenseSymmetricMatrixGpu<RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::DenseSymmetricMatrixGpu<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::DenseVectorGpu<_Val>;
  using MatrixType  = matrix::DenseSymmetricMatrixGpu<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseSymmetricMatrixGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseSymmetricMatrixGpu
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseSymmetricMatrixGpu<matrix::DenseSymmetricMatrixGpu<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix assert.
///
#define assertDenseSymmetricMatrixGpu( Type ) \
    static_assert(traits::IsDenseSymmetricMatrixGpu<Type>::value, "'"#Type"' is not a dense symmetric matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_gpu_module
/// The dense symmetric matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class SyMatS<GpuTag, DenseTag, _Val, _trans, _uplo>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseSymmetricMatrixGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseSymmetricMatrixBase<GpuTag, _Val, _trans, _uplo> {

 private:

  using BaseType = DenseSymmetricMatrixBase<GpuTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseSymmetricMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  matrix_dense_gpu_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSymmetricMatrixGpuColMajor = DenseSymmetricMatrixGpu<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_gpu_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseSymmetricMatrixGpuRowMajor = DenseSymmetricMatrixGpu<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_GPU_HH_
