////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  int a;
  char c;

  std::cin >> a;
  c = std::cin.get();
  disp(a);
  disp(c);

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
// #ifdef _OPENMP
//               << omp_get_max_threads()
// #else  // _OPENMP
//               << 1
// #endif  // _OPENMP
//               << " threads per node" << std::endl << std::endl;
//   }

//   int n = 8, lda = 10;
//   mcnla::matrix::DenseMatrixRowMajor<double> a(n, n, lda);

//   mcnla::random::Streams streams(0);
//   mcnla::random::gaussian(streams, a.vec());
//   disp(a);

//   mcnla::la::getrfi(a);
//   disp(a);

//   mcnla::finalize();

  return 0;
}
