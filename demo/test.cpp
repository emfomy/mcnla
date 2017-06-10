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
              << " threads per node" << std::endl << std::endl;
  }

  int m = 5, n = 8, lda = 10;
  mcnla::matrix::DenseMatrixRowMajor<double> a(m, n, lda);
  mcnla::matrix::DenseVector<double> d(m);
  mcnla::matrix::DenseVector<double> e(m-1);
  mcnla::matrix::DenseVector<double> tauq(m);
  mcnla::matrix::DenseVector<double> taup(m);

  mcnla::matrix::DenseVector<double> work;

  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vec());
  disp(a);

  auto lwork1 = mcnla::la::gebrdQuery(a);
  disp(lwork1);
  work.reconstruct(lwork1);
  mcnla::la::gebrd(a, d, e, tauq, taup, work);

  mcnla::matrix::DenseMatrixRowMajor<double> u(m, m);
  mcnla::la::memset0(u.vec());
  for ( auto i = 0; i < m; ++i ) {
    u(i, i) = 1;
  }

  auto lwork2 = mcnla::la::ormbrQuery<mcnla::la::Vect::Q>(a, u, tauq);
  disp(lwork2);
  work.reconstruct(lwork2);
  mcnla::la::ormbr<mcnla::la::Vect::Q>(a, u, tauq, work);

  mcnla::matrix::DenseMatrixRowMajor<double> vt(n, n);
  mcnla::la::memset0(vt.vec());
  for ( auto i = 0; i < n; ++i ) {
    vt(i, i) = 1;
  }

  auto lwork3 = mcnla::la::ormbrQuery<mcnla::la::Vect::PT>(a, taup, vt);
  disp(lwork3);
  work.reconstruct(lwork3);
  mcnla::la::ormbr<mcnla::la::Vect::PT>(a, taup, vt, work);

  auto vt1 = vt({0, m}, ""_);
  auto lwork4 = mcnla::la::bdsqrQuery(a);
  disp(lwork4);
  work.reconstruct(lwork4);
  mcnla::la::bdsqr(a, d, e, u, vt1, work);

  mcnla::la::mm(""_, d.diag(), u);
  mcnla::la::mm(u, vt1, a);
  disp(a);

  mcnla::finalize();

  return 0;
}
