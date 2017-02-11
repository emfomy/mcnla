////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <iostream>
#include <mcnla.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

#include <algorithm>
#include <vector>
#include <functional>

using Pair = std::tuple<int, int>;
using RPair = std::tuple<int&, int&>;

struct PRPair {
  RPair rpair;
  PRPair( const RPair& rpair ) noexcept : rpair(rpair) {}
  inline RPair* operator->() noexcept { return &rpair; }
};

struct Iter : public std::iterator<std::random_access_iterator_tag, Pair> {

  std::vector<int> &vec1;
  std::vector<int> &vec2;
  int idx;
  int size;

  Iter( std::vector<int> &vec1, std::vector<int> &vec2, int idx = 0 ) noexcept : vec1(vec1), vec2(vec2), idx(idx) {
    size = std::min(vec1.size(), vec2.size());
  }

  // Assignment operators
  inline Iter& operator=( const Iter &other ) noexcept { vec1 = other.vec1; vec2 = other.vec2; idx = other.idx; return *this; }

  // Member access operators
  inline RPair operator*() const noexcept { return std::tie(vec1[idx], vec2[idx]); }
  inline PRPair operator->() const noexcept { return PRPair(std::tie(vec1[idx], vec2[idx])); }

  // Comparison operators
  inline bool operator==( const Iter &other ) const noexcept { return idx == other.idx; }
  inline bool operator!=( const Iter &other ) const noexcept { return idx != other.idx; }
  inline bool operator>(  const Iter &other ) const noexcept { return idx > other.idx; }
  inline bool operator<(  const Iter &other ) const noexcept { return idx < other.idx; }
  inline bool operator>=( const Iter &other ) const noexcept { return idx >= other.idx; }
  inline bool operator<=( const Iter &other ) const noexcept { return idx <= other.idx; }

  // Arithmetic operators
  inline Iter& operator++() noexcept { if ( ++idx > size ) { idx = size; } return *this; }
  inline Iter& operator--() noexcept { if ( --idx < 0 ) { idx = 0; } return *this; }
  inline Iter  operator++( int ) noexcept { auto retval(*this); ++(*this); return retval; }
  inline Iter  operator--( int ) noexcept { auto retval(*this); --(*this); return retval; }
  inline Iter& operator+=( const int num ) noexcept { if ( (idx += num) > size ) { idx = size; } return *this; }
  inline Iter& operator-=( const int num ) noexcept { if ( (idx -= num) > size ) { idx = size; } return *this; }
  inline Iter  operator+(  const int num ) const noexcept { auto retval(*this); return (retval += num); }
  inline Iter  operator-(  const int num ) const noexcept { auto retval(*this); return (retval -= num); }

  inline int operator-( const Iter &other ) const noexcept { return (idx - other.idx); }
  friend inline Iter operator+( const int num, const Iter iter ) noexcept { return (iter + num); }

};

inline bool operator<( const RPair &a, const RPair &b ) {
  if ( std::get<0>(a) != std::get<0>(b) ) {
    return (std::get<0>(a) < std::get<0>(b));
  } else {
    return (std::get<1>(a) < std::get<1>(b));
  }
}

namespace std {
  inline void swap( const RPair a, const RPair b ) {
    swap(get<0>(a), get<0>(b));
    swap(get<1>(a), get<1>(b));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  // int a0 = 1, a1 = 2, b0 = 3, b1 = 4;
  // RPair pa = std::tie(a0, a1), pb = std::tie(b0, b1);
  // std::swap(pa, pb);
  // std::cout << a0 << a1 << b0 << b1 << std::endl << std::endl;

  // int n = 10;

  // std::vector<int> vec1(n);
  // std::vector<int> vec2(n);

  // int i = 0;
  // for ( auto &v : vec1 ) {
  //   v = (++i) % 3;
  // }
  // for ( auto &v : vec2 ) {
  //   v = (++i) % 4;
  // }

  // for ( auto it = Iter(vec1, vec2, 0); it != Iter(vec1, vec2, n); ++it ) {
  //   std::cout << std::get<0>(*it) << ", " << std::get<1>(*it) << std::endl;
  // }
  // std::cout << std::endl;

  // std::sort(Iter(vec1, vec2, 0), Iter(vec1, vec2, n));

  // for ( auto it = Iter(vec1, vec2, 0); it != Iter(vec1, vec2, n); ++it ) {
  //   std::cout << std::get<0>(*it) << ", " << std::get<1>(*it) << std::endl;
  // }
  // std::cout << std::endl;

  // auto it = std::lower_bound(Iter(vec1, vec2, 0), Iter(vec1, vec2, n), std::make_tuple(1, 2));

  // std::cout << std::get<0>(*it) << ", " << std::get<1>(*it) << ' ' << it.idx << std::endl;
  // it->swap(pb);
  // std::cout << std::get<0>(*it) << ", " << std::get<1>(*it) << ' ' << it.idx << std::endl;

  return 0;
}
