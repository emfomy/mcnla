////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_symmetric_gpu_matrix.hh
/// @brief   The definition of dense symmetric GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/dense/def.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix_base.hpp>
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
/// The dense symmetric matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseSymmetricGpuMatrix<_Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::DenseSymmetricGpuMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::DenseSymmetricGpuMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseSymmetricGpuMatrix<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseSymmetricGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseSymmetricGpuMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseSymmetricGpuMatrix<matrix::DenseSymmetricGpuMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix assert.
///
#define assertDenseSymmetricGpuMatrix( Type ) \
    static_assert(traits::IsDenseSymmetricGpuMatrix<Type>::value, "'"#Type"' is not a dense symmetric matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense symmetric matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
class DenseSymmetricGpuMatrix : public DenseSymmetricMatrixBase<_Val, _trans, _uplo, DenseGpuTypes> {

 private:

  using BaseType = DenseSymmetricMatrixBase<_Val, _trans, _uplo, DenseGpuTypes>;

 public:

  using BaseType::DenseSymmetricMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  gpu_matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSymmetricGpuMatrixColMajor = DenseSymmetricGpuMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  gpu_matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseSymmetricGpuMatrixRowMajor = DenseSymmetricGpuMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_SYMMETRIC_GPU_MATRIX_HH_
