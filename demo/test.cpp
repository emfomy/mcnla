////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <cstdio>
#include <iostream>
#include <mcnla.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  int n = 7, nnz = 9;

  using DataType = std::tuple<mcnla::index_t, mcnla::index_t, double>;
  std::vector<DataType> data(nnz);

  int i = 1, j = 2, jj = 2, k = 3, kk = 3;
  for ( auto &value : data ) {
    value = std::make_tuple(i++, (((j += 3) %= n) + ((jj *= 3) %= n)) % n, (((k += 4) %= n) + ((kk *= 4) %= n)) % n);
  }

  std::sort(data.begin(), data.end(), []( DataType &i, DataType&j ) {
    return (std::get<1>(i) == std::get<1>(j) ? std::get<0>(i) < std::get<0>(j) : std::get<1>(i) < std::get<1>(j));
  } );

  mcnla::matrix::CooMatrixRowMajor<double> mat(n, n, nnz);

  for ( auto i = 0; i < nnz; ++i ) {
    mat.val().valarray()[i] = std::get<0>(data[i]);
    mat.rowidx().valarray()[i] = std::get<1>(data[i]);
    mat.colidx().valarray()[i] = std::get<2>(data[i]);
  }

  for ( auto i = 0; i < nnz; ++i ) {
    std::cout << mat.rowidxPtr()[i] << mat.colidxPtr()[i] << mat.valPtr()[i] << std::endl;
  }

  std::cout << mat << std::endl;
  std::cout << mat(1, "") << std::endl;

  return 0;
}
