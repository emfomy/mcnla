////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_data.hpp
/// @brief   The dense data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_DATA_HPP_
#define ISVD_MATRIX_DENSE_DENSE_DATA_HPP_

#include <isvd/isvd.hpp>
#include <valarray>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense data storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseData {

 private:

  using ValuePtrType = std::shared_ptr<std::valarray<_Scalar>>;

 protected:

  /// The data array.
  ValuePtrType value_;

  /// The empty data array
  static const ValuePtrType kNullValue;

 public:

  // Constructors
  inline DenseData() noexcept;
  inline DenseData( const index_t capability ) noexcept;
  inline DenseData( const ValuePtrType &value ) noexcept;
  inline DenseData( const DenseData &other ) noexcept;
  inline DenseData( DenseData &&other ) noexcept;

  // Operators
  inline DenseData& operator=( const DenseData &other ) noexcept;
  inline DenseData& operator=( DenseData &&other ) noexcept;
  inline bool operator==( const DenseData& other ) const noexcept;
  inline bool operator!=( const DenseData& other ) const noexcept;
  inline       _Scalar* operator*() noexcept;
  inline const _Scalar* operator*() const noexcept;

  // Gets data
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;
  inline       index_t  getCapability() const noexcept;

};

template <typename _Scalar>
const typename DenseData<_Scalar>::ValuePtrType DenseData<_Scalar>::kNullValue = std::make_shared<std::valarray<_Scalar>>();

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_DATA_HPP_
