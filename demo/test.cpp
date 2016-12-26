////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

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

  MPI_Init(&argc, &argv);
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::mpi_int_t mpi_size = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::getCommRank(MPI_COMM_WORLD);

  int m = 3, n = 8;

  // {
  //   mcnla::matrix::DenseVector<double> vec1(m);
  //   mcnla::matrix::DenseVector<double> vec2(m);

  //   int i = 0;
  //   for ( auto &v : vec1 ) {
  //     v = 100 * mpi_rank + (++i);
  //   }

  //   std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl;

  //   mcnla::mpi::bcast(vec1, vec2, mpi_root, MPI_COMM_WORLD);

  //   std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl;

  //   mcnla::mpi::bcast(vec1, mpi_root, MPI_COMM_WORLD);

  //   std::cout << mpi_rank << '\n' << vec1 << vec2 << std::endl;
  // }

  {
    mcnla::matrix::DenseMatrix<double> mat1(m, n);
    mcnla::matrix::DenseMatrix<double> mat2(m, n);

    int i = 0;
    for ( auto &v : mat1 ) {
      v = 100 * mpi_rank + (++i);
    }

    // std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl;

    // mcnla::mpi::bcast(mat1, mat2, mpi_root, MPI_COMM_WORLD);

    std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl;

    mcnla::mpi::bcast(mat1, mpi_root, MPI_COMM_WORLD);

    std::cout << mpi_rank << '\n' << mat1 << mat2 << std::endl;
  }

  // {
  //   mcnla::matrix::DenseMatrixColMajor<double> mat1(m, n);
  //   mcnla::matrix::DenseMatrixRowMajor<double> mat2(n, m);

  //   int i = 0;
  //   for ( auto &v : mat1 ) {
  //     v = 100 * mpi_rank + (++i);
  //   }


  //   std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl;

  //   mcnla::mpi::bcast(mat1, mat2, mpi_root, MPI_COMM_WORLD);


  //   std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl;

  //   mcnla::mpi::bcast(mat1, mpi_root, MPI_COMM_WORLD);


  //   std::cout << mpi_rank << '\n' << mat1 << mat2.t() << std::endl;
  // }

  MPI_Finalize();

  return 0;
}
