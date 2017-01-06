////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <cstdio>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  int n = 1000000000;

  mcnla::matrix::DenseVector<double> vec(n);

  mcnla::random::GaussianEngine<double> rand(1);

  std::cout << "omp_size = " << rand.ompSize() << std::endl;

  double t0 = omp_get_wtime();
  rand(vec);
  double t1 = omp_get_wtime();

  printf("time = %.2lfs\n", t1-t0);

  double sum = 0.0, sum2 = 0.0;
  for ( auto i = 0; i < n; ++i ) sum += vec(i);
  for ( auto i = 0; i < n; ++i ) sum2 += vec(i) * vec(i);
  sum /= n; sum2 /= n;
  printf("mu = %16.12lf, sigma = %16.12lf\n", sum, sqrt(sum2-sum*sum));

  return 0;
}
