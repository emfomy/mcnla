////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>

#pragma warning
#include <mcnla/core/la/raw/lapack/ormlq.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  mcnla::init(argc, argv);

  const auto mpi_comm = MPI_COMM_WORLD;
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(mpi_comm);
  mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(mpi_comm);
  mcnla::mpi_int_t mpi_root = 0;

  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

    std::cout << mpi_size << " nodes / "
#ifdef _OPENMP
              << omp_get_max_threads()
#else  // _OPENMP
              << 1
#endif  // _OPENMP
              << " threads per node" << std::endl;
    std::cout << sizeof(mcnla::index_t)*8 << "bit integer" << std::endl << std::endl;
  }

  mcnla::index_t m = 8, n = 5;
  mcnla::matrix::DenseMatrixRowMajor<double> a(m, n), q0(m, n), c0(n, m), cq(n, n), tmp;
  auto c = c0(""_, {0, n});
  auto q = q0({0, n}, ""_);
  mcnla::matrix::DenseVector<double> tau(n);

  mcnla::random::Streams stream(0);
  mcnla::random::gaussian(stream, a.vec());
  disp(a);

  mcnla::random::gaussian(stream, c0.vec());
  for ( auto &v : c0(""_, {n, m}) ) {
    v = 0;
  }
  disp(c0);
  disp(c);

  mcnla::la::geqrfg<'S', 'N'>(a, tau, q0, tmp);
  disp(q0);
  disp(q);
  mcnla::la::mm(c, q, cq);
  disp(cq);

  double lwork;
  mcnla::la::detail::ormlq('L', 'N', m, n, n, a.valPtr(), a.pitch(), tau.valPtr(), c0.valPtr(), c0.pitch(), &lwork, -1);
  mcnla::matrix::DenseVector<double> work(lwork);
  mcnla::la::detail::ormlq('L', 'N', m, n, n, a.valPtr(), a.pitch(), tau.valPtr(), c0.valPtr(), c0.pitch(), work.valPtr(),
                           lwork);
  disp(c0);
  disp(c);

  mcnla::finalize();

  return 0;
}
