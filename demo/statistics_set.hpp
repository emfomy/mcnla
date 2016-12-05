////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/statistics_set.hpp
/// @brief   The statistics set
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_DEMO_STATISTICS_SET_HPP_
#define MCNLA_DEMO_STATISTICS_SET_HPP_

#include <iomanip>
#include <valarray>

class StatisticsSet {

 private:

  std::valarray<double> set_;
  std::valarray<double> diff_;
  size_t size_;

 public:

  inline StatisticsSet( const int capacity )
    : set_(capacity),
      diff_(capacity),
      size_(0) {};

  inline void operator()( const double value ) {
    assert(size_ < set_.size()); set_[size_++] = value;
  }

  inline double mean() {
    return set_.sum() / set_.size();
  }

  inline double var() {
    diff_ = set_ - mean();
    diff_ *= diff_;
    return diff_.sum() / diff_.size();
  };

  inline double sd() {
    return std::sqrt(var());
  };
};

#endif  // MCNLA_DEMO_STATISTICS_SET_HPP_
