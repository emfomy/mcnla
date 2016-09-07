////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_data.hpp
/// @brief   The dense data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DATA_HPP_
#define ISVD_MATRIX_DENSE_DATA_HPP_

#include <memory>
#include <isvd/isvd.hpp>

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

 protected:

  /// The length of data array.
  index_t capability_;

  /// The data array.
  std::shared_ptr<_Scalar> value_;

 public:

  // Constructors
  DenseData() noexcept;
  DenseData( const index_t capability ) noexcept;
  DenseData( const index_t capability, std::shared_ptr<_Scalar> value ) noexcept;
  DenseData( const DenseData &other ) noexcept;
  DenseData( DenseData &&other ) noexcept;

  // Operators
  inline DenseData& operator=( const DenseData &other ) noexcept;
  inline DenseData& operator=( DenseData &&other ) noexcept;
  inline bool operator==( const DenseData& other ) const noexcept;
  inline bool operator!=( const DenseData& other ) const noexcept;
  inline       _Scalar* operator*() noexcept;
  inline const _Scalar* operator*() const noexcept;

  // Gets data
  inline        index_t getCapability() const noexcept;
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DATA_HPP_
