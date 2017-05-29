////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>

#define DATA_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

//   mcnla::init(argc, argv);

//   const auto mpi_comm = MPI_COMM_WORLD;
//   mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(mpi_comm);
//   mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(mpi_comm);
//   mcnla::mpi_int_t mpi_root = 0;

//   if ( mpi_rank == mpi_root ) {
//     std::cout << "MCNLA "
//               << MCNLA_MAJOR_VERSION << "."
//               << MCNLA_MINOR_VERSION << "."
//               << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

//     std::cout << mpi_size << " nodes / "
// #ifdef MCNLA_USE_OMP
//               << omp_get_max_threads()
// #else  //MCNLA_USE_OMP
//               << 1
// #endif  // MCNLA_USE_OMP
//               << " threads per node" << std::endl << std::endl;
//   }

//   int m = 5, n = 8, lda = 10;
//   auto ptr = new double[n*lda];
//   std::shared_ptr<double> sptr(ptr, std::default_delete<double[]>());

//   mcnla::matrix::Array<double> array(sptr, n*lda);
//   mcnla::matrix::DenseMatrixColMajor<double> a(m, n, lda, array);

//   mcnla::finalize();

  return 0;
}
