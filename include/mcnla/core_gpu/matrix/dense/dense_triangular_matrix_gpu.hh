////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_triangular_matrix_gpu.hh
/// @brief   The definition of GPU triangular dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
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
/// The GPU dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularMatrixGpu : std::false_type {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularMatrixGpu<matrix::DenseTriangularMatrixGpu<_Val, _trans, _uplo>> : std::true_type {};
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularMatrixGpu( Type ) \
    static_assert(traits::IsDenseTriangularMatrixGpu<Type>::value, "'"#Type"' is not a GPU dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_gpu_module
/// The dense triangular matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class TrMatS<GpuTag, DenseTag, _Val, _trans, _uplo>
  : public DenseTriangularMatrixBase<GpuTag, _Val, _trans, _uplo> {
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseTriangularMatrixGpu
  : public DenseTriangularMatrixBase_<GpuTag, _Val, _trans, _uplo> {
#endif  // DOXYGEN_SHOULD_SKIP_THIS

 private:

  using BaseType = DenseTriangularMatrixBase<GpuTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseTriangularMatrixBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseTriangularMatrixBase_::operator=
  DenseTriangularMatrixGpu& operator=( const DenseTriangularMatrixGpu &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Copy
  inline void copy() const noexcept = delete;

};

/// @ingroup  matrix_dense_gpu_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixGpuColMajor = DenseTriangularMatrixGpu<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_gpu_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularMatrixGpuRowMajor = DenseTriangularMatrixGpu<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_GPU_HH_
