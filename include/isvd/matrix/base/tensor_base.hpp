////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/tensor_base.hpp
/// @brief   The tensor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_MATRIX_BASE_TENSOR_BASE_HPP_
#define ISVD_MATRIX_BASE_TENSOR_BASE_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of tensor type.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class TensorBase {

 protected:

  // Constructors
  inline TensorBase() noexcept {};

};

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_TENSOR_BASE_HPP_
