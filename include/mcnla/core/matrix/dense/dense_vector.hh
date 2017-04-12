////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.hh
/// @brief   The definition of dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/dense_vector_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
#include <mcnla/core/matrix/dense/dense_vector_iterator.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix.hpp>
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
template <typename _Val> class DenseVector;
template <typename _Val> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector traits.
///
template <typename _Val>
struct Traits<matrix::DenseVector<_Val>> {
  static constexpr index_t ndim = 1;

  using ValType           = _Val;

  using RealType          = matrix::DenseVector<RealValT<_Val>>;
  using ComplexType       = matrix::DenseVector<ComplexValT<_Val>>;

  using VectorType        = matrix::DenseVector<_Val>;

  using IteratorType      = matrix::DenseVectorIterator<_Val>;
  using ConstIteratorType = matrix::DenseVectorConstIterator<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector instantiation type traits.
///
template <typename _Type>
struct IsDenseVector : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseVector
///
template <typename _Val>
struct IsDenseVector<matrix::DenseVector<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector assert.
///
#define assertDenseVector( Type ) \
    static_assert(traits::IsDenseVector<Type>::value, "'"#Type"' is not a dense vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseVector
  : public DenseVectorStorage<_Val>,
    public DenseVectorWrapper<DenseVector<_Val>>,
    public IterableWrapper<DenseVector<_Val>>,
    public InvertibleWrapper<DenseVector<_Val>> {

  friend VectorWrapper<DenseVector<_Val>>;
  friend DenseVectorWrapper<DenseVector<_Val>>;
  friend IterableWrapper<DenseVector<_Val>>;
  friend InvertibleWrapper<DenseVector<_Val>>;

 public:

  static constexpr index_t ndim = 1;

  using ValType           = _Val;
  using ValArrayType      = Array<_Val>;
  using SizesType         = std::tuple<index_t>;

  using RealType          = DenseVector<RealValT<_Val>>;
  using ComplexType       = DenseVector<ComplexValT<_Val>>;

  using VectorType        = DenseVector<_Val>;

  using DiagonalType      = DenseDiagonalMatrix<_Val>;

  using IteratorType      = DenseVectorIterator<_Val>;
  using ConstIteratorType = DenseVectorConstIterator<_Val>;

 private:

  using BaseType          = DenseVectorStorage<_Val>;

 public:

  // Constructors
  inline DenseVector() noexcept;
  inline DenseVector( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseVector( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVector( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseVector( const DenseVector &other ) noexcept;
  inline DenseVector( DenseVector &&other ) noexcept;

  // Operators
  inline DenseVector& operator=( const DenseVector &other ) noexcept;
  inline DenseVector& operator=( DenseVector &&other ) noexcept;

  // Copy
  inline DenseVector copy() const noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets element
  inline       ValType& operator()( const index_t idx ) noexcept;
  inline const ValType& operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_
