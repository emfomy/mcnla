////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_vector.hh
/// @brief   The definition of dense GPU vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/base/vector_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/kit/gpu_array.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class DenseGpuVector;
template <typename _Val> class DenseGpuDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector traits.
///
template <typename _Val>
struct Traits<matrix::DenseGpuVector<_Val>> {
  static constexpr index_t ndim = 1;

  using ValType     = _Val;

  using RealType    = matrix::DenseGpuVector<RealValT<_Val>>;
  using ComplexType = matrix::DenseGpuVector<ComplexValT<_Val>>;

  using VectorType  = matrix::DenseGpuVector<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector instantiation type traits.
///
template <typename _Type>
struct IsDenseGpuVector : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseGpuVector
///
template <typename _Val>
struct IsDenseGpuVector<matrix::DenseGpuVector<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU vector assert.
///
#define assertDenseGpuVector( Type ) \
    static_assert(traits::IsDenseGpuVector<Type>::value, "'"#Type"' is not a dense GPU vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense GPU vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseGpuVector
  : public DenseVectorStorage<_Val, GpuArray>,
    public VectorWrapper<DenseGpuVector<_Val>>,
    public InvertibleWrapper<DenseGpuVector<_Val>> {

  friend VectorWrapper<DenseGpuVector<_Val>>;
  friend InvertibleWrapper<DenseGpuVector<_Val>>;

 public:

  static constexpr index_t ndim = 1;

  using ValType      = _Val;
  using ValArrayType = GpuArray<_Val>;
  using SizesType    = std::tuple<index_t>;

  using RealType     = DenseGpuVector<RealValT<_Val>>;
  using ComplexType  = DenseGpuVector<ComplexValT<_Val>>;

  using VectorType   = DenseGpuVector<_Val>;

  using DiagonalType = DenseGpuDiagonalMatrix<_Val>;

 private:

  using BaseType     = DenseVectorStorage<_Val, GpuArray>;

 public:

  // Constructors
  inline DenseGpuVector() noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseGpuVector( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseGpuVector( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride,
                         const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseGpuVector( const DenseGpuVector &other ) noexcept;

  // Operators
  inline DenseGpuVector& operator=( const DenseGpuVector &other ) noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t length ) noexcept;
  inline void resize( const index_t length, const index_t stride ) noexcept;

  // Changes view
  inline       DiagonalType& viewDiagonal() noexcept;
  inline const DiagonalType& viewDiagonal() const noexcept;

  // Gets segment
  inline       VectorType operator()( const IdxRange &range ) noexcept;
  inline const VectorType operator()( const IdxRange &range ) const noexcept;

 protected:

  // Gets information
  inline index_t lengthImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t length ) const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
