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

  // isvd::CooData<3, double> data;
  // std::cout << data.getValuePtr() << std::endl
  //           << data.getIdxPtr<0>() << std::endl
  //           << data.getIdxPtr<1>() << std::endl;
  // auto data01 = data.getReduced<0, 1>();
  // std::cout << data01.getValuePtr() << std::endl
  //           << data01.getIdxPtr<0>() << std::endl
  //           << data01.getIdxPtr<1>() << std::endl;

  // const isvd::CooData<3, double> cdata;
  // std::cout << cdata.getValuePtr() << std::endl
  //           << cdata.getIdxPtr<0>() << std::endl
  //           << cdata.getIdxPtr<1>() << std::endl;
  // auto cdata01 = cdata.getReduced<0, 1>();
  // std::cout << cdata01.getValuePtr() << std::endl
  //           << cdata01.getIdxPtr<0>() << std::endl
  //           << cdata01.getIdxPtr<1>() << std::endl;

  // isvd::CooCube<double, isvd::Layout::COLMAJOR> mat(10, 20, 6, 3, 5);

  // int i = 0;
  // for ( auto tuple : mat ) {
  //   ++i;
  //   tuple(i, i+2, i*i, 7-i*2);
  // }

  // std::cout << mat << std::endl;
  // mat.sort();
  // std::cout << mat << std::endl;
  // std::cout << mat(4, 4, 4) << std::endl;
  // std::cout << mat(4, 4, 3) << std::endl << std::endl;
  // std::cout << mat.getCols(3, {0, 5}) << std::endl;
  // std::cout << mat.getColSegment(1, 5, {0, 5}) << std::endl;

}
