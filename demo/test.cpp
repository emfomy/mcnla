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

  std::array<std::shared_ptr<int>, 3> idx{std::shared_ptr<int>(new int[3]), std::shared_ptr<int>(new int[4]), std::shared_ptr<int>(new int[5])};
  auto idx2 = std::move(idx);
  for ( auto i = 0; i < 3; ++i ) {
    std::cout << idx2[i].get() << std::endl;
  }
}
