////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.hpp
/// @brief   The dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <mcnla/core/matrix/base/container_base.hpp>
#include <mcnla/core/matrix/base/vector_base.hpp>
#include <mcnla/core/matrix/dense/dense_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<matrix::DenseVector<_Scalar>> {
  static constexpr index_t ndim = 1;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;

  using VectorType        = matrix::DenseVector<ScalarType>;
  using RealVectorType    = matrix::DenseVector<RealScalarType>;

  using IteratorType      = matrix::DenseVectorIterator<ScalarType>;
  using ConstIteratorType = matrix::DenseVectorConstIterator<ScalarType>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVector
  : public ContainerBase<DenseVector<_Scalar>>,
    public VectorBase<DenseVector<_Scalar>>,
    public DenseBase<DenseVector<_Scalar>> {

 public:

  static constexpr index_t ndim = 1;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;
  using ValueArrayType    = Array<ScalarType>;

  using VectorType        = DenseVector<ScalarType>;
  using RealVectorType    = DenseVector<RealScalarType>;

  using DataType          = DenseData<ScalarType>;

  using IteratorType      = DenseVectorIterator<ScalarType>;
  using ConstIteratorType = DenseVectorConstIterator<ScalarType>;

 private:

  using ContainerBaseType = ContainerBase<DenseVector<_Scalar>>;
  using VectorBaseType    = VectorBase<DenseVector<_Scalar>>;
  using DenseBaseType     = DenseBase<DenseVector<_Scalar>>;

 protected:

  /// The stride.
  index_t stride_;

  using VectorBaseType::length_;
  using DenseBaseType::data_;

 public:

  // Constructors
  inline DenseVector() noexcept;
  inline DenseVector( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const ValueArrayType &value ) noexcept;
  inline DenseVector( const index_t length, const index_t stride, const DataType &data, const index_t offset = 0 ) noexcept;
  inline DenseVector( const DenseVector &other ) noexcept;
  inline DenseVector( DenseVector &&other ) noexcept;

  // Operators
  inline DenseVector& operator=( const DenseVector &other ) noexcept;
  inline DenseVector& operator=( DenseVector &&other ) noexcept;
  template <typename __Scalar>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseVector<__Scalar> &vector );

  // Gets information
  inline index_t getStride() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t idx ) noexcept;
  inline const ScalarType& getElem( const index_t idx ) const noexcept;
  inline       ScalarType& operator()( const index_t idx ) noexcept;
  inline const ScalarType& operator()( const index_t idx ) const noexcept;

  // Gets mask
  inline const std::gslice getValueMask() const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t idx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

  // Resizes
  inline void resize( const index_t length, const index_t stride ) noexcept;

  // Gets segment
  inline       VectorType getSegment( const IdxRange range ) noexcept;
  inline const VectorType getSegment( const IdxRange range ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
