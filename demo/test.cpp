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

  const std::valarray<int> a(10);
  for ( auto i = 0; i < 10; ++i ) {
    const_cast<int&>(a[i]) = i;
  }
  std::valarray<int>    b = a[std::slice(0, 5, 2)];
  std::_Expr<std::_SClos<std::_ValArray, int>, int> &&c = a[std::slice(0, 5, 2)];

  const int *a1 = &a[0];
  int *b1 = &b[0];

  for ( auto i = 0; i < 10; ++i ) {
    std::cout << a[i] << '\t';
  }
  std::cout << std::endl;
  for ( auto i = 0; i < 10; ++i ) {
    std::cout << a1[i] << '\t';
  }
  std::cout << std::endl;
  for ( auto i = 0; i < 10; ++i ) {
    std::cout << b[i] << '\t';
  }
  std::cout << std::endl;
  for ( auto i = 0; i < 10; ++i ) {
    std::cout << b1[i] << '\t';
  }
  std::cout << std::endl;

}
