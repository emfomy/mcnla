////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/stage_wrapper.hh
/// @brief   The definition of iSVD stage wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CORE_STAGE_WRAPPER_HH_
#define MCNLA_ISVD_CORE_STAGE_WRAPPER_HH_

#include <mcnla/isvd/def.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <mcnla/isvd/core/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/time.hpp>

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
/// The iSVD stage wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class StageWrapper {

 public:

  using ValType = ValT<_Derived>;

 protected:

  /// The parameters
  const Parameters<ValType> &parameters_;

  /// The tag shows if the stage is initialized.
  bool initialized_ = false;

  /// The tag shows if the stage is computed.
  bool computed_ = false;

  /// The moment of running each part of the stage.
  std::vector<double> moments_;

  /// The time of communication of each part of the stage.
  std::vector<double> comm_times_;

 protected:

  // Constructor
  inline StageWrapper( const Parameters<ValType> &parameters ) noexcept;

 public:

  // Initializes
  template <typename... Args>
  inline void initialize( Args... arg ) noexcept;

  // Operators
  template <typename... Args>
  inline void operator()( Args... arg ) noexcept;
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const StageWrapper<__Derived> &wrapper ) noexcept;

  // Gets data
  inline bool isInitialized() const noexcept;
  inline bool isComputed() const noexcept;

  // Gets compute time
  inline double time() const noexcept;
  inline double commTime() const noexcept;
  inline std::vector<double> times() const noexcept;
  inline std::vector<double> commTimes() const noexcept;
  inline std::vector<double> moments() const noexcept;
  inline const char* names() const noexcept;

 protected:

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Record time
  inline void tic() noexcept;
  inline void toc( double &comm_time ) noexcept;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_DERIVED(_Derived);
#endif  // DOXYGEN_SHOULD_SKIP_THIS


};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_STAGE_WRAPPER_HH_
