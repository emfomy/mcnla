////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_base.hpp
/// @brief   The dense interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_BASE_HPP_
#define ISVD_MATRIX_DENSE_BASE_HPP_

#include <memory>
#include <isvd/config.hpp>
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
/// @tparam  _Scalar   The scalar type of matrix.
///
template <class _Derived, typename _Scalar>
class DenseBase : public CrtpBase<_Derived, DenseBase<_Derived, _Scalar>> {

 public:

  // Gets matrix information
  inline index_t getCapability() const noexcept;

  // Gets data
  inline _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_BASE_HPP_
