////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <unistd.h>

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
  mcnla::mpi_int_t mpi_size = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::getCommRank(MPI_COMM_WORLD);

  int m = 3, n = 8, K = mpi_size;

  bool tmp;

  // {
  //   mcnla::matrix::DenseVector<double> vec1(n);
  //   mcnla::matrix::DenseVector<double> vec2(n);

  //   int i = 0;
  //   for ( auto &v : vec1 ) {
  //     v = 100 * mpi_rank + (++i);
  //   }

  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);

  //   mcnla::mpi::reduce(vec1, vec2, MPI_SUM, mpi_root, MPI_COMM_WORLD);
  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);

  //   mcnla::mpi::reduce(vec1, MPI_SUM, mpi_root, MPI_COMM_WORLD);
  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);
  // }

  // {
  //   mcnla::matrix::DenseMatrix<double> mat1(m, n);
  //   mcnla::matrix::DenseMatrix<double> mat2(m, n);

  //   int i = 0;
  //   for ( auto &v : mat1 ) {
  //     v = 100 * mpi_rank + (++i);
  //   }

  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);

  //   mcnla::mpi::reduce(mat1, mat2, MPI_SUM, mpi_root, MPI_COMM_WORLD);
  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);

  //   mcnla::mpi::reduce(mat1, MPI_SUM, mpi_root, MPI_COMM_WORLD);
  //   usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl; MPI_Barrier(MPI_COMM_WORLD);
  // }

  {
    mcnla::matrix::DenseMatrixColMajor<double> mat1(m, n);
    mcnla::matrix::DenseMatrixRowMajor<double> mat2(n, m);

    int i = 0;
    for ( auto &v : mat1 ) {
      v = 100 * mpi_rank + (++i);
    }

    usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl; MPI_Barrier(MPI_COMM_WORLD);

    mcnla::mpi::reduce(mat1, mat2, MPI_SUM, mpi_root, MPI_COMM_WORLD);
    usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl; MPI_Barrier(MPI_COMM_WORLD);

    mcnla::mpi::reduce(mat1, MPI_SUM, mpi_root, MPI_COMM_WORLD);
    usleep(1000*mpi_rank); std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl; MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
