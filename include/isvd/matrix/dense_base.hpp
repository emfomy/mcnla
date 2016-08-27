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
#include <isvd/utility/crtp.hpp>

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
  const index_t capability_;

  /// The data array.
  std::shared_ptr<_Scalar> value_;

 public:

  // Constructors
  DenseData() noexcept;
  DenseData( const index_t capability ) noexcept;
  DenseData( const index_t capability, _Scalar *value ) noexcept;

  // Destructor
  ~DenseData() noexcept;

  // Gets data
  inline        index_t getCapability() const noexcept;
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of matrix.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class DenseBase : public CrtpBase<_Derived, DenseBase<_Derived>> {

 private:
  using ScalarType = typename Traits<_Derived>::ScalarType;

 public:

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
