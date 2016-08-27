////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.hpp
/// @brief   The dense vector class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense_vector_base.hpp>

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
  using ScalarType = _Scalar;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVector : public internal::DenseVectorBase<DenseVector<_Scalar>> {

  friend internal::VectorBase<DenseVector<_Scalar>>;
  friend internal::DenseBase<DenseVector<_Scalar>>;
  friend internal::DenseVectorBase<DenseVector<_Scalar>>;

 protected:

  /// The number of entries.
  index_t length_;

  /// The increment.
  const index_t increment_;

  /// The offset of starting position.
  const index_t offset_;

  /// The data storage
  DenseData<_Scalar> data_;

 public:

  // Constructors
  DenseVector() noexcept;
  DenseVector( const index_t length, const index_t increment = 1 ) noexcept;
  DenseVector( const index_t length, const index_t increment, _Scalar *value ) noexcept;
  DenseVector( const index_t length, const index_t increment, _Scalar *value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseVector( const index_t length, const index_t increment,
               const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;

  // Destructor
  ~DenseVector() noexcept;

 protected:

  // Operators
  template <typename __Scalar>
  friend std::ostream& operator<<( std::ostream &out, const DenseVector<__Scalar> &vector );

  // Gets information
  inline index_t getLengthImpl() const noexcept;
  inline index_t getIncrementImpl() const noexcept;
  inline index_t getOffsetImpl() const noexcept;

  // Gets data storage
  inline DenseData<_Scalar>& getDataImpl() noexcept;
  inline const DenseData<_Scalar>& getDataImpl() const noexcept;

  // Gets element
  inline       _Scalar& getElementImpl( const index_t idx ) noexcept;
  inline const _Scalar& getElementImpl( const index_t idx ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t length ) noexcept;

  // Gets segment
  inline DenseVector getSegmentImpl( const IndexRange range ) noexcept;

  // Gets internal information
  inline index_t getIndexInternal( const index_t idx ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_HPP_
