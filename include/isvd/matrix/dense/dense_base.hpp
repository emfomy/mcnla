////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_base.hpp
/// @brief   The dense interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_BASE_HPP_
#define ISVD_MATRIX_DENSE_DENSE_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/dense/dense_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of dense type.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseBase {

 private:

  using ScalarType = typename Traits<_Derived>::ScalarType;
  using DataType   = DenseData<ScalarType>;

 protected:

  /// The offset of starting position.
  index_t offset_;

  /// The data storage
  DataType data_;

 public:

  // Constructors
  DenseBase() noexcept;
  DenseBase( const index_t capability, const index_t offset = 0 ) noexcept;
  DenseBase( const index_t capability, std::shared_ptr<ScalarType> value, const index_t offset = 0 ) noexcept;
  DenseBase( const DataType& data, const index_t offset = 0 ) noexcept;
  DenseBase( const DenseBase &other ) noexcept;
  DenseBase( DenseBase &&other ) noexcept;

  // Operators
  inline DenseBase& operator=( const DenseBase &other ) noexcept;
  inline DenseBase& operator=( DenseBase &&other ) noexcept;

  // Gets information
  inline index_t getCapability() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data storage
  inline DataType& getData() noexcept;
  inline const DataType& getData() const noexcept;

  // Gets data array
  inline ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_BASE_HPP_