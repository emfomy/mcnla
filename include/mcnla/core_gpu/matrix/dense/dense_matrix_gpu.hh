////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_matrix_gpu.hh
/// @brief   The definition of definition of  GPU dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_MATRIX_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_MATRIX_GPU_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_base.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_vector_gpu.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_symmetric_matrix_gpu.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_triangular_matrix_gpu.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_matrix_gpu.hpp>
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
/// The GPU dense matrix traits.
///
template <typename _Val, Trans _trans>
struct Traits<matrix::GeMatI<GpuTag, DenseTag, _Val, _trans>> {

  static constexpr Trans trans = _trans;

  using ValType     = _Val;

  using RealType    = matrix::GeMatI<GpuTag, DenseTag, RealValT<_Val>, _trans>;
  using ComplexType = matrix::GeMatI<GpuTag, DenseTag, ComplexValT<_Val>, _trans>;

  using VectorType  = matrix::GeVecI<GpuTag, DenseTag, _Val>;
  using MatrixType  = matrix::GeMatI<GpuTag, DenseTag, _Val, _trans>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU dense matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseMatrixGpu : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseMatrixGpu
///
template <typename _Val, Trans _trans>
struct IsDenseMatrixGpu<matrix::GeMatI<GpuTag, DenseTag, _Val, _trans>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU dense matrix assert.
///
#define assertDenseMatrixGpu( Type ) \
    static_assert(traits::IsDenseMatrixGpu<Type>::value, "'"#Type"' is not a GPU dense matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_gpu_module
/// The GPU dense matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans>
class GeMatI<GpuTag, DenseTag, _Val, _trans> : public DenseMatrixBase<GpuTag, _Val, _trans> {

 private:

  using BaseType = DenseMatrixBase<GpuTag, _Val, _trans>;

 public:

  using BaseType::DenseMatrixBase;

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

/// @ingroup  matrix_dense_gpu_module
template <typename _Val, Trans _trans = Trans::NORMAL>
using DenseMatrixGpu = GeMatI<GpuTag, DenseTag, _Val, _trans>;

/// @ingroup  matrix_dense_gpu_module
template <typename _Val>
using DenseMatrixGpuColMajor = GeMatI<GpuTag, DenseTag, _Val, Trans::NORMAL>;

/// @ingroup  matrix_dense_gpu_module
template <typename _Val>
using DenseMatrixGpuRowMajor = GeMatI<GpuTag, DenseTag, _Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_MATRIX_GPU_HH_
