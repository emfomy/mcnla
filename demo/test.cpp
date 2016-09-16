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

  isvd::DenseMatrix<double> mat(3, 5);
  auto it = std::lower_bound(mat.cibegin().toValueIterator().toIdxIterator(), mat.cend().toIdxIterator(), isvd::makeIdxTuple(2, 4));
  std::cout << it.getRowIdx() << it.getColIdx() << std::endl;

}
