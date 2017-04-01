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
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);

  mcnla::index_t m = 10, n = 10, k = 5, p = 1, l = k+p, Nj = 2, seed = rand();

  mcnla::matrix::DenseMatrixColMajor<double> a(m, n);
  mcnla::matrix::DenseMatrixCollection120<double> qs(m, l, Nj);
  mcnla::matrix::DenseMatrixRowMajor<double> qbar(m, l);

  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vectorize());
  mcnla::mpi::bcast(a, mpi_root, MPI_COMM_WORLD);

  mcnla::isvd::Parameters parameters(MPI_COMM_WORLD, mpi_root, seed);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters);
  // mcnla::isvd::ColumnSamplingSketcher<double> sketcher(parameters);
  mcnla::isvd::SvdOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::KolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);

  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();

  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  sketcher(a, qs);
  orthogonalizer(qs);
  integrator(qs, qbar);
  former(a, qbar);

  auto u = former.matrixU();

  disp(a);
  disp(u);

  mcnla::matrix::DenseMatrixColMajor<double> uu(k, k);
  mcnla::la::mm(u.t(), u, uu);

  disp(uu);

  MPI_Finalize();

  return 0;
}
