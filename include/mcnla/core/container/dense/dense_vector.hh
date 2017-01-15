////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/dense/dense_vector.hh
/// @brief   The definition of dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HH_
#define MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/container/base/vector_wrapper.hpp>
#include <mcnla/core/container/base/container_wrapper.hpp>
#include <mcnla/core/container/dense/dense_vector_storage.hpp>
#include <mcnla/core/container/dense/dense_vector_iterator.hpp>
#include <mcnla/core/container/dense/dense_diagonal_matrix.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseVector;
template <typename _Scalar> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace container

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector traits.
///
template <typename _Scalar>
struct Traits<container::DenseVector<_Scalar>> {
  static constexpr index_t ndim = 1;

  using ScalarType        = _Scalar;

  using RealType          = container::DenseVector<RealScalarT<_Scalar>>;
  using ComplexType       = container::DenseVector<ComplexScalarT<_Scalar>>;

  using VectorType        = container::DenseVector<_Scalar>;

  using IteratorType      = container::DenseVectorIterator<_Scalar>;
  using ConstIteratorType = container::DenseVectorConstIterator<_Scalar>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_dense_module
/// The dense vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVector
  : public DenseVectorStorage<_Scalar>,
    public VectorWrapper<DenseVector<_Scalar>>,
    public ContainerWrapper<DenseVector<_Scalar>> {

  friend VectorWrapper<DenseVector<_Scalar>>;
  friend ContainerWrapper<DenseVector<_Scalar>>;

 public:

  static constexpr index_t ndim = 1;

  using ScalarType        = _Scalar;
  using ValueArrayType    = Array<_Scalar>;
  using SizesType         = std::tuple<index_t>;

  using RealType          = DenseVector<RealScalarT<_Scalar>>;
  using ComplexType       = DenseVector<ComplexScalarT<_Scalar>>;

  using VectorType        = DenseVector<_Scalar>;

  using DiagonalType      = DenseDiagonalMatrix<_Scalar>;

  using IteratorType      = DenseVectorIterator<_Scalar>;
  using ConstIteratorType = DenseVectorConstIterator<_Scalar>;

 private:

  using BaseType          = DenseVectorStorage<_Scalar>;

 public:

  // Constructors
  inline DenseVector() noexcept;
  inline DenseVector( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseVector( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVector( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVector( const index_t length, const index_t stride,
                      const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseVector( const DenseVector &other ) noexcept;
  inline DenseVector( DenseVector &&other ) noexcept;

  // Operators
  inline DenseVector& operator=( const DenseVector &other ) noexcept;
  inline DenseVector& operator=( DenseVector &&other ) noexcept;

  // Gets information
  inline index_t nidx() const noexcept;

  // Gets element
  inline       ScalarType& operator()( const index_t idx ) noexcept;
  inline const ScalarType& operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t length, const index_t stride = 1 ) noexcept;

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

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_DENSE_DENSE_VECTOR_HH_
