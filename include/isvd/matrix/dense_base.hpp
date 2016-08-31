////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_base.hpp
/// @brief   The dense interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_BASE_HPP_
#define ISVD_MATRIX_DENSE_BASE_HPP_

#include <memory>
#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/dense_data.hpp>

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
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class DenseBase {

 private:

  using ScalarType = typename Traits<_Derived>::ScalarType;

 protected:

  /// The offset of starting position.
  index_t offset_;

  /// The data storage
  DenseData<ScalarType> data_;

 public:

  // Constructors
  DenseBase() noexcept;
  DenseBase( const index_t capability, const index_t offset = 0 ) noexcept;
  DenseBase( const index_t capability, ScalarType *value, const index_t offset = 0 ) noexcept;
  DenseBase( const index_t capability, std::shared_ptr<ScalarType> value, const index_t offset = 0 ) noexcept;
  DenseBase( const DenseData<ScalarType>& data, const index_t offset = 0 ) noexcept;

  // Gets information
  inline index_t getCapability() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data storage
  inline DenseData<ScalarType>& getData() noexcept;
  inline const DenseData<ScalarType>& getData() const noexcept;

  // Operators
  inline ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_BASE_HPP_
