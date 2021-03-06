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
    const Parameters<_Val> &parameters
) noexcept
  : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived> template <typename ..._Args>
void StageWrapper<_Derived>::initialize(
    _Args... args
) noexcept {
  mcnla_assert_true(parameters_.isSynchronized());
  derived().initializeImpl(args...);
  moments_.clear();
  comm_times_.clear();
  initialized_ = true;
  computed_ = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Run the stage.
///
template <class _Derived> template <typename ..._Args>
void StageWrapper<_Derived>::operator()(
    _Args... args
) noexcept {
  mcnla_assert_true(parameters_.isSynchronized());
  mcnla_assert_true(isInitialized());
  moments_.clear();
  comm_times_.clear();
  derived().runImpl(args...);
  computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output name to stream.
///
template <typename ..._Args>
std::ostream& operator<<(
    std::ostream &os,
    const StageWrapper<_Args...> &wrapper
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
  return derived().outputNameImpl(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  outputName
///
///
template <class _Derived>
std::ostream& StageWrapper<_Derived>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << derived().name_);
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
  return derived().names_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Record the starting time.
///
template <class _Derived>
void StageWrapper<_Derived>::tic(
    double &comm_time
) noexcept {
  mcnla_assert_true(moments_.empty());
  mcnla_assert_true(comm_times_.empty());
  moments_.emplace_back(utility::getTime());
  comm_time = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Record the ending time of current part.
///
/// @note  @a comm_time will be reset to zero.
///
template <class _Derived>
void StageWrapper<_Derived>::toc(
    double &comm_time
) noexcept {
  mcnla_assert_false(moments_.empty());
  moments_.emplace_back(utility::getTime());
  comm_times_.emplace_back(comm_time);
  comm_time = 0.0;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_STAGE_WRAPPER_HPP_
