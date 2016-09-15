////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/container_base.hpp
/// @brief   The container interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CONTAINER_BASE_HPP_
#define ISVD_MATRIX_CONTAINER_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ContainerBase : protected CrtpBase<_Derived, ContainerBase<_Derived>> {

 private:

  using IteratorType         = typename Traits<_Derived>::IteratorType;
  using ConstIteratorType    = typename Traits<_Derived>::ConstIteratorType;
  using IdxIteratorType      = typename Traits<_Derived>::IdxIteratorType;
  using ConstIdxIteratorType = typename Traits<_Derived>::ConstIdxIteratorType;

 protected:

  // Constructors
  inline ContainerBase() noexcept {};

 public:

  // Gets iterator
  inline IteratorType         begin() noexcept;
  inline ConstIteratorType    begin() const noexcept;
  inline ConstIteratorType    cbegin() const noexcept;
  inline IteratorType         end() noexcept;
  inline ConstIteratorType    end() const noexcept;
  inline ConstIteratorType    cend() const noexcept;
  inline IdxIteratorType      ibegin() noexcept;
  inline ConstIdxIteratorType ibegin() const noexcept;
  inline ConstIdxIteratorType cibegin() const noexcept;
  inline IdxIteratorType      iend() noexcept;
  inline ConstIdxIteratorType iend() const noexcept;
  inline ConstIdxIteratorType ciend() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CONTAINER_BASE_HPP_
