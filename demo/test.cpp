////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

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

  mcnla::matrix::DenseMatrixSet120<double> set(8, 2, 3);
  int i = mpi_rank * 100;
  for ( auto &v : set.getData() ) {
    v = i; i++;
  }

  if ( mpi_rank == mpi_root ) {
    std::cout << set.unfold() << std::endl;
  }

  mcnla::mpi::alltoall(set.unfold(), MPI_COMM_WORLD);

  if ( mpi_rank == mpi_root ) {
    std::cout << set.unfold() << std::endl;
  }

  MPI_Finalize();

  return 0;
}
