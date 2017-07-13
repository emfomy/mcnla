////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_matrix_gpu.hh
/// @brief   The definition of GPU dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_

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
/// The GPU dense diagonal matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalMatrixGpu : std::false_type {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
struct IsDenseDiagonalMatrixGpu<matrix::DenseDiagonalMatrixGpu<_Val>> : std::true_type {};
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix assert.
///
#define assertDenseDiagonalMatrixGpu( Type ) \
    static_assert(traits::IsDenseDiagonalMatrixGpu<Type>::value, "'"#Type"' is not a GPU dense diagonal matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_gpu_module
/// The dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DiMatS<GpuTag, DenseTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseDiagonalMatrixGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseDiagonalMatrixBase<GpuTag, _Val> {

 private:

  using BaseType = DenseDiagonalMatrixBase<GpuTag, _Val>;

 public:

  using BaseType::DenseDiagonalMatrixBase;
  using BaseType::operator();

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseDiagonalMatrixBase::operator=
  DenseDiagonalMatrixGpu& operator=( const DenseDiagonalMatrixGpu &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Copy
  inline void copy() const noexcept = delete;

  // Gets element
  inline void operator()( const index_t rowidx, const index_t colidx ) noexcept = delete;
  inline void operator()( const index_t rowidx, const index_t colidx ) const noexcept = delete;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_GPU_HH_
