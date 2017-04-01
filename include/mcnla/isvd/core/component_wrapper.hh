////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/component_wrapper.hh
/// @brief   The definition of iSVD component wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CORE_COMPONENT_WRAPPER_HH_
#define MCNLA_ISVD_CORE_COMPONENT_WRAPPER_HH_

#include <mcnla/isvd/def.hpp>
#include <iostream>
#include <vector>
#include <mcnla/isvd/core/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_core_module_detail
/// The iSVD component wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ComponentWrapper : public utility::CrtpBase<_Derived, ComponentWrapper<_Derived>> {

 public:

  using ValType = ValT<_Derived>;

 protected:

  /// The parameters
  const Parameters &parameters_;

  /// The tag shows if the component is initialized.
  bool initialized_ = false;

  /// The tag shows if the component is computed.
  bool computed_ = false;

 protected:

  // Constructor
  inline ComponentWrapper( const Parameters &parameters ) noexcept;

 public:

  // Initializes
  template <typename... Args>
  inline void initialize( Args... arg ) noexcept;

  // Operators
  template <typename... Args>
  inline void operator()( Args... arg ) noexcept;
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const ComponentWrapper<__Derived> &wrapper );

  // Gets compute time
  inline double time() const noexcept;
  inline std::vector<double> times() const noexcept;
  inline std::vector<double> moments() const noexcept;

 protected:

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;

  // Gets data
  inline bool isInitialized() const noexcept;
  inline bool isComputed() const noexcept;


};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_COMPONENT_WRAPPER_HH_