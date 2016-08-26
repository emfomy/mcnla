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
//  The implementation namespace.
//
namespace impl {

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

  // Gets data
  inline ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_BASE_HPP_
