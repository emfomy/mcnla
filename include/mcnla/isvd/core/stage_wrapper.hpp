////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/stage_wrapper.hpp
/// @brief   The iSVD stage wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CORE_STAGE_WRAPPER_HPP_
#define MCNLA_ISVD_CORE_STAGE_WRAPPER_HPP_

#include <mcnla/isvd/core/stage_wrapper.hh>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
StageWrapper<_Derived>::StageWrapper(
    const Parameters<ValType> &parameters
) noexcept
  : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived> template <typename... Args>
void StageWrapper<_Derived>::initialize(
    Args... args
) noexcept {
  mcnla_assert_true(parameters_.isSynchronized());
  this->derived().initializeImpl(args...);
  moments_.clear();
  comm_times_.clear();
  initialized_ = true;
  computed_ = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Run the stage.
///
template <class _Derived> template <typename... Args>
void StageWrapper<_Derived>::operator()(
    Args... args
) noexcept {
  mcnla_assert_true(parameters_.isSynchronized());
  mcnla_assert_true(isInitialized());
  moments_.clear();
  comm_times_.clear();
  this->derived().runImpl(args...);
  computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output name to stream.
///
template <class __Derived>
std::ostream& operator<<(
    std::ostream &os,
    const StageWrapper<__Derived> &wrapper
) noexcept {
  return wrapper.outputName(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<
///
template <class _Derived>
std::ostream& StageWrapper<_Derived>::outputName(
    std::ostream &os
) const noexcept {
  return this->derived().outputNameImpl(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  outputName
///
///
template <class _Derived>
std::ostream& StageWrapper<_Derived>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << this->derived().name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the parameters is initialized.
///
template <class _Derived>
bool StageWrapper<_Derived>::isInitialized() const noexcept {
  return initialized_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the parameters is computed.
///
template <class _Derived>
bool StageWrapper<_Derived>::isComputed() const noexcept {
  return computed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running the stage.
///
template <class _Derived>
double StageWrapper<_Derived>::time() const noexcept {
  if ( moments_.empty() ) {
    return 0;
  }
  return moments_.back() - moments_.front();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of communication.
///
template <class _Derived>
double StageWrapper<_Derived>::commTime() const noexcept {
  return std::accumulate(comm_times_.begin(), comm_times_.end(), 0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the times of running each part of the stage.
///
template <class _Derived>
std::vector<double> StageWrapper<_Derived>::times() const noexcept {
  mcnla_assert_true(isComputed());
  std::vector<double> times(moments_.size());
  std::adjacent_difference(moments_.begin(), moments_.end(), times.begin());
  times.erase(times.begin());
  return times;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of communication of each part of the stage.
///
template <class _Derived>
std::vector<double> StageWrapper<_Derived>::commTimes() const noexcept {
  return comm_times_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the moment of running each part of the stage.
///
template <class _Derived>
std::vector<double> StageWrapper<_Derived>::moments() const noexcept {
  return moments_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the name of each part of the stage.
///
template <class _Derived>
const char* StageWrapper<_Derived>::names() const noexcept {
  return this->derived().names_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_STAGE_WRAPPER_HPP_
