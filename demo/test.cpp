////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  isvd::DenseVector<double> vec(3, 5);
  auto it = std::lower_bound(vec.cibegin().toValueIterator().toIdxIterator(), vec.cend().toIdxIterator(), isvd::IdxTuple<double, 1>({3}));
  std::cout << it.getIdx() << std::endl;

}
