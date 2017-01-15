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

  mcnla::index_t m = 5, n = 7;

  mcnla::container::DenseDiagonalMatrix<double> al(m);
  mcnla::container::DenseDiagonalMatrix<double> ar(n);
  mcnla::container::DenseMatrixColMajor<double> b(m, n);
  mcnla::container::DenseMatrixColMajor<double> c(m, n);

  // mcnla::random::gaussian(a.vectorize(), 0);
  // mcnla::random::gaussian(b.vectorize(), 1);
  // mcnla::random::gaussian(c.vectorize(), 2);

  int i = 0;
  for ( auto &v : al.viewVector() ) {
    v = ++i;
  }
  i = 0;
  for ( auto &v : ar.viewVector() ) {
    v = ++i;
  }
  for ( auto &v : b ) {
    v = 1;
  }

  std::cout << al << std::endl;
  std::cout << ar << std::endl;
  std::cout << b << std::endl;

  mcnla::blas::mm(al, "", b);

  std::cout << b << std::endl;

  mcnla::blas::mm("", ar, b);

  std::cout << b << std::endl;

  // MPI_Init(&argc, &argv);
  // mcnla::mpi_int_t mpi_root = 0;
  // mcnla::index_t m = 10, n = 20, k = 5, p = 1, Nj = 3, seed = 0;

  // mcnla::isvd::Parameters parameters(MPI_COMM_WORLD);
  // parameters.nrow_ = m;
  // parameters.ncol_ = n;
  // parameters.rank_ = k;
  // parameters.over_rank_ = p;
  // parameters.num_sketch_each_ = Nj;

  // parameters.initialized_ = true;
  // parameters.computed_ = true;

  // mcnla::container::DenseMatrixColMajor<double> mat(m, n);
  // mcnla::container::DenseMatrixCollection120<double> collection(m, k+p, Nj);

  // mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters, MPI_COMM_WORLD, mpi_root, seed);
  // sketcher.setSeed(1);
  // sketcher.initialize();
  // // mcnla::random::gaussian(mat.vectorize(), 0);
  // int i = 0;
  // for ( auto &v : mat ) {
  //   v = ++i;
  // }

  // sketcher.sketch(mat, collection);

  // for ( auto i = 0; i < Nj; ++i ) {
  //   std::cout << collection(i) << std::endl;
  // }

  // mcnla::isvd::SvdOrthogonalizer<double> orthogonalizer(parameters, MPI_COMM_WORLD, mpi_root);
  // orthogonalizer.initialize();

  // orthogonalizer.orthogonalize(collection);

  // for ( auto i = 0; i < Nj; ++i ) {
  //   std::cout << collection(i) << std::endl;
  // }

  // mcnla::isvd::SvdFormer<double> former(parameters, MPI_COMM_WORLD, mpi_root);
  // former.initialize();

  // former.form(mat, collection(0));

  // std::cout << former.vectorS() << std::endl;
  // std::cout << former.matrixU() << std::endl;
  // std::cout << former.matrixVt() << std::endl;

  // mcnla::isvd::DummyFormer<double> d_former(parameters, MPI_COMM_WORLD, mpi_root);
  // d_former.initialize();

  // d_former.form(mat, collection(0));

  // MPI_Finalize();

  return 0;
}
