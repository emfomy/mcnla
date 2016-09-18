////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

#include <isvd/matrix/coo/coo_tuple.hpp>
#include <isvd/matrix/coo/coo_tuple.ipp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  char c1 = 'a', c2 = 'b';
  int i1[] = {1, 2, 3}, i2[] = {4, 5, 6};

  auto coo = isvd::makeCooTuple(1, 3, 2);
  auto r1 = isvd::makeRefCooTuple(c1, i1[0], i1[1], i1[2]);
  auto r2 = isvd::makeRefCooTuple(c2, i2[0], i2[1], i2[2]);

  std::cout << (coo == r1) << std::endl;
  std::cout << (coo < r1) << std::endl;
  std::cout << (coo > r1) << std::endl;

  std::cout << std::get<0>(coo) << std::get<1>(coo) << std::get<2>(coo) << std::endl;
  std::cout << std::get<0>(r1) << std::get<1>(r1) << std::get<2>(r1) << std::get<3>(r1) << std::endl;
  std::cout << std::get<0>(r2) << std::get<1>(r2) << std::get<2>(r2) << std::get<3>(r2) << std::endl;

  std::swap(std::move(r1), std::move(r2));

  std::cout << std::get<0>(r1) << std::get<1>(r1) << std::get<2>(r1) << std::get<3>(r1) << std::endl;
  std::cout << std::get<0>(r2) << std::get<1>(r2) << std::get<2>(r2) << std::get<3>(r2) << std::endl;

  std::cout << i1[0] << i1[1] << i1[2] << c1 << std::endl;
  std::cout << i2[0] << i2[1] << i2[2] << c2 << std::endl;

  // auto it = boost::make_tuple(it0, ait0);
  // std::cout << it->get<0>() << std::endl;
  // auto it = std::lower_bound(zit0, zit1, boost::make_tuple(3, 5), comp);
  // std::cout << it->get<0>() << std::endl;

  // auto it = std::lower_bound(it0, it1, 3);
  // std::cout << *it << std::endl;

  // std::sort(zit0, zit1, comp);
  // for ( auto it = it0; it != it1; ++it ) {
  //   std::cout << *it << std::endl;
  // }
}
