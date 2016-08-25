////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.hpp
/// @brief   The dense vector class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_HPP_

#include <memory>
#include <isvd/config.hpp>
#include <isvd/matrix/dense_vector_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector class.
///
/// @tparam  _Scalar  The scalar type of matrix.
/// @tparam  _layout  The storage layout of matrix.
///
//@{
template <typename _Scalar>
class DenseVector : public impl::DenseVectorBase<DenseVector<_Scalar>, _Scalar> {

  friend impl::VectorBase<DenseVector<_Scalar>>;
  friend impl::DenseBase<DenseVector<_Scalar>, _Scalar>;
  friend impl::DenseVectorBase<DenseVector<_Scalar>, _Scalar>;

 protected:

  /// The number of entries.
  const index_t length_;

  /// The increment.
  const index_t increment_;

  /// The offset of starting position.
  const index_t offset_;

  /// The length of data array.
  const index_t capability_;

  /// The data array.
  std::shared_ptr<_Scalar> value_;

 public:

  // Constructors
  DenseVector() noexcept;
  DenseVector( const index_t length, const index_t increment = 1 ) noexcept;
  DenseVector( const index_t length, const index_t increment, _Scalar *value ) noexcept;
  DenseVector( const index_t length, const index_t increment, _Scalar *value,
               const index_t capability, const index_t offset = 0 ) noexcept;

  // Destructor
  ~DenseVector() noexcept;

 protected:

  // Constructors
  DenseVector( const DenseVector &other, const index_t length, const index_t offset ) noexcept;

  // Operators
  template <typename __Scalar>
  friend std::ostream& operator<< ( std::ostream &out, const DenseVector<__Scalar> &vector );

  // Gets matrix information
  inline index_t getLengthImpl() const noexcept;
  inline index_t getIncrementImpl() const noexcept;
  inline index_t getOffsetImpl() const noexcept;
  inline index_t getCapabilityImpl() const noexcept;

  // Gets data
  inline       _Scalar* getValueImpl() noexcept;
  inline const _Scalar* getValueImpl() const noexcept;
  inline       _Scalar& getValueImpl( const index_t idx ) noexcept;
  inline const _Scalar& getValueImpl( const index_t idx ) const noexcept;

  // Gets segment
  inline DenseVector getSegmentImpl( const index_t idx, const index_t length ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_HPP_
