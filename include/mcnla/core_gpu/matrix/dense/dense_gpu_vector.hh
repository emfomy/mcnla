////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_vector.hh
/// @brief   The definition of dense GPU vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core_gpu/matrix/kit/gpu_array.hpp>

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
template <typename _Val> class DenseDiagonalGpuMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

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
class DenseGpuVector : public DenseVector<_Val> {

 public:

  using ValType           = _Val;
  using ValArrayType      = GpuArray<_Val>;
  using SizesType         = std::tuple<index_t>;

  using RealType          = DenseGpuVector<RealValT<_Val>>;
  using ComplexType       = DenseGpuVector<ComplexValT<_Val>>;

  using VectorType        = DenseGpuVector<_Val>;

  using DiagonalType      = DenseDiagonalGpuMatrix<_Val>;

  using IteratorType      = void;
  using ConstIteratorType = void;

 private:

  using BaseType          = DenseVector<_Val>;

 public:

  // Constructors
  inline DenseGpuVector() noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseGpuVector( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseGpuVector( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseGpuVector( const index_t length, const index_t stride, const ValArrayType &val,
                         const index_t offset = 0 ) noexcept;
  inline DenseGpuVector( const DenseGpuVector &other ) noexcept;

  // Operators
  inline DenseGpuVector& operator=( const DenseGpuVector &other ) noexcept;
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const DenseGpuVector<__Derived> &vector ) = delete;

  // Copy
  inline DenseGpuVector copy() const noexcept = delete;

  // Gets element
  inline       ValType& operator()( const index_t idx ) noexcept = delete;
  inline const ValType& operator()( const index_t idx ) const noexcept = delete;

  // Gets iterator
  inline IteratorType      begin() noexcept = delete;
  inline ConstIteratorType begin() const noexcept = delete;
  inline ConstIteratorType cbegin() const noexcept = delete;
  inline IteratorType      end() noexcept = delete;
  inline ConstIteratorType end() const noexcept = delete;
  inline ConstIteratorType cend() const noexcept = delete;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept = delete;
  inline ConstIteratorType find( const index_t idx ) const noexcept = delete;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept = delete;

  // Changes view
  inline       DiagonalType& viewDiagonal() noexcept;
  inline const DiagonalType& viewDiagonal() const noexcept;

  // Gets segment
  inline       VectorType operator()( const IdxRange &range ) noexcept;
  inline const VectorType operator()( const IdxRange &range ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_VECTOR_HH_
