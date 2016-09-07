////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.hpp
/// @brief   The dense vector class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/vector_base.hpp>
#include <isvd/matrix/dense_base.hpp>
#include <isvd/matrix/dense_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class DenseVector;
template <typename _Scalar> class DenseVectorIterator;

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

  using IteratorType   = internal::DenseVectorIterator<ScalarType>;

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
  DenseVector( const index_t length, const index_t increment, std::shared_ptr<_Scalar> value ) noexcept;
  DenseVector( const index_t length, const index_t increment, std::shared_ptr<_Scalar> value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseVector( const index_t length, const index_t increment,
               const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;
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

  // Gets iterator
  inline       IteratorType begin() noexcept;
  inline const IteratorType begin() const noexcept;
  inline       IteratorType end() noexcept;
  inline const IteratorType end() const noexcept;

  // Gets element
  inline       _Scalar& getElem( const index_t idx ) noexcept;
  inline const _Scalar& getElem( const index_t idx ) const noexcept;
  inline       _Scalar& operator()( const index_t idx ) noexcept;
  inline const _Scalar& operator()( const index_t idx ) const noexcept;

  // Resizes
  inline void resize( const index_t length ) noexcept;

  // Gets segment
  inline       DenseVector<_Scalar> getSegment( const IndexRange range ) noexcept;
  inline const DenseVector<_Scalar> getSegment( const IndexRange range ) const noexcept;

 protected:

  // Gets internal information
  inline index_t getIndexInternal( const index_t idx ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_HPP_
