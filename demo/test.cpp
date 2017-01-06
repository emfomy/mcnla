////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

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

  MPI_Init(&argc, &argv);
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::index_t m = 10, n = 20, k = 5, p = 1, Nj = 4, seed = 0;

  mcnla::isvd::Parameters<double> parameters(MPI_COMM_WORLD);
  parameters.nrow_ = m;
  parameters.ncol_ = n;
  parameters.rank_ = k;
  parameters.over_rank_ = p;
  parameters.num_sketch_each_ = Nj;
  parameters.tolerance_ = 1e-4;
  parameters.max_iteration_ = 256;

  mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters, MPI_COMM_WORLD, mpi_root, seed);
  // mcnla::isvd::ColumnSamplingSketcher<double> sketcher(parameters, MPI_COMM_WORLD, mpi_root, seed);

  sketcher.setSeed(1);
  sketcher.initialize();
  parameters.initialized_ = true;

  mcnla::matrix::DenseMatrixColMajor<double> mat(m, n);
  mcnla::matrix::DenseMatrixSet120<double> set(m, k+p, Nj);

  // mcnla::random::gaussian(mat.vectorize(), 0);
  int i = 0;
  for ( auto &v : mat ) {
    v = ++i;
  }

  sketcher.sketch(mat, set);

  for ( auto i = 0; i < Nj; ++i ) {
    std::cout << set(i) << std::endl;
  }

  MPI_Finalize();

  return 0;
}
