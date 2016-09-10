////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector.hpp
/// @brief   The dense vector class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/vector_base.hpp>
#include <isvd/matrix/dense/dense_base.hpp>
#include <isvd/matrix/dense/dense_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class DenseVector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<DenseVector<_Scalar>> {
  using ScalarType     = _Scalar;
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVector
  : public internal::VectorBase<DenseVector<_Scalar>>,
    public internal::DenseBase<DenseVector<_Scalar>> {

 public:

  using ScalarType     = _Scalar;
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;

  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;

  using DataType          = DenseData<ScalarType>;
  using IteratorType      = DenseVectorIterator<ScalarType>;
  using ConstIteratorType = DenseVectorConstIterator<ScalarType>;

 private:

  using VectorBaseType = internal::VectorBase<DenseVector<ScalarType>>;
  using DenseBaseType  = internal::DenseBase<DenseVector<ScalarType>>;

 protected:

  /// The increment.
  index_t increment_;

  using VectorBaseType::length_;
  using DenseBaseType::offset_;
  using DenseBaseType::data_;

 public:

  // Constructors
  DenseVector() noexcept;
  DenseVector( const index_t length, const index_t increment = 1 ) noexcept;
  DenseVector( const index_t length, const index_t increment, std::shared_ptr<ScalarType> value ) noexcept;
  DenseVector( const index_t length, const index_t increment, std::shared_ptr<ScalarType> value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseVector( const index_t length, const index_t increment, const DataType &data, const index_t offset = 0 ) noexcept;
  DenseVector( const DenseVector &other ) noexcept;
  DenseVector( DenseVector &&other ) noexcept;

  // Operators
  inline DenseVector& operator=( const DenseVector &other ) noexcept;
  inline DenseVector& operator=( DenseVector &&other ) noexcept;
  template <typename __Scalar>
  friend std::ostream& operator<<( std::ostream &out, const DenseVector<__Scalar> &vector );

  // Gets information
  inline index_t getIncrement() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t idx ) noexcept;
  inline const ScalarType& getElem( const index_t idx ) const noexcept;
  inline       ScalarType& operator()( const index_t idx ) noexcept;
  inline const ScalarType& operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t idx ) const noexcept;

  // Gets iterator
  inline IteratorType      begin() noexcept;
  inline ConstIteratorType begin() const noexcept;
  inline ConstIteratorType cbegin() const noexcept;
  inline IteratorType      end() noexcept;
  inline ConstIteratorType end() const noexcept;
  inline ConstIteratorType cend() const noexcept;
  inline IteratorType      getIterator( const index_t idx ) noexcept;
  inline ConstIteratorType getIterator( const index_t idx ) const noexcept;
  inline ConstIteratorType getConstIterator( const index_t idx ) const noexcept;

  // Resizes
  inline void resize( const index_t length ) noexcept;

  // Gets segment
  inline       DenseVector getSegment( const IdxRange range ) noexcept;
  inline const DenseVector getSegment( const IdxRange range ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_HPP_
