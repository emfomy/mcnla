////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

#define TEST_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::DenseMatrixSet120<double> set;
  mcnla::io::loadMatrixMarket(set, TEST_PATH);
  std::cout << set.unfold() << std::endl;

  // MPI_Init(&argc, &argv);
  // mcnla::mpi_int_t mpi_size = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  // mcnla::mpi_int_t mpi_rank = mcnla::mpi::getCommRank(MPI_COMM_WORLD);

  // int K = mpi_size, n = 3;

  // int a[K*n], b[n];

  // int counts[] = {n, n, n, n};

  // for ( auto i = 0; i < K; ++i ) {
  //   for ( auto j = 0; j < n; ++j ) {
  //     a[i*n+j] = 100*mpi_rank + 10*i + j;
  //   }
  // }

  // for ( auto k = 0; k < mpi_size; ++k ) {
  //   MPI_Barrier(MPI_COMM_WORLD);
  //   if ( k == mpi_rank ) {
  //     std::cout << mpi_rank << std::endl;
  //     for ( auto i = 0; i < K; ++i ) {
  //       for ( auto j = 0; j < n; ++j ) {
  //         std::cout << a[i*n+j] << '\t';
  //       }
  //       std::cout << std::endl;
  //     }
  //     std::cout << std::endl << std::flush;
  //   }
  // }

  // MPI_Reduce_scatter(a, b, counts, MPI_INTEGER, MPI_SUM, MPI_COMM_WORLD);

  // for ( auto k = 0; k < mpi_size; ++k ) {
  //   MPI_Barrier(MPI_COMM_WORLD);
  //   if ( k == mpi_rank ) {
  //     std::cout << mpi_rank << std::endl;
  //     for ( auto j = 0; j < n; ++j ) {
  //       std::cout << b[j] << '\t';
  //     }
  //     std::cout << std::endl << std::endl << std::flush;
  //   }
  // }

  // MPI_Finalize();

  return 0;
}
