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

  auto mpi_comm = MPI_COMM_WORLD;
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(mpi_comm);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(mpi_comm);

  mcnla::index_t m = 10, n = 10, k = 5, p = 1, l = k+p, Nj = 2, K = mpi_size, N = Nj*K, seed = rand();

  mcnla::matrix::DenseMatrixColMajor<double> a(m, n);
  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vectorize());
  mcnla::mpi::bcast(a, mpi_root, mpi_comm);

  mcnla::isvd::Parameters parameters(mpi_comm, mpi_root, seed);
  parameters.setSize(a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  auto m_full = parameters.nrowTotal(), mj = parameters.nrowEach();

  mcnla::matrix::DenseMatrixCollection120<double> qi(m_full, l, Nj);
  mcnla::matrix::DenseMatrixCollection120<double> qij(mj, l, N);
  mcnla::matrix::DenseMatrixRowMajor<double> qbar(m, l);
  mcnla::matrix::DenseMatrixRowMajor<double> qbarj(mj, l);
  qi   = qi({0, m}, "", "");
  qbar = qbar({0, m}, "");

  mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters);
  mcnla::isvd::SvdOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();

  mcnla::isvd::CollectionQToRowBlockConverter<double> oi_converter(parameters);
  mcnla::isvd::MatrixQFromRowBlockConverter<double> if_converter(parameters);
  oi_converter.initialize();
  if_converter.initialize();

  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  sketcher(a, qi);
  orthogonalizer(qi);
  oi_converter(qi, qij);
  integrator(qij, qbarj);
  if_converter(qbarj, qbar);
  former(a, qbar);

  auto &u = former.matrixU();

  disp(a);
  disp(u);

  mcnla::matrix::DenseMatrixColMajor<double> uu(k, k);
  mcnla::la::mm(u.t(), u, uu);

  disp(uu);

  MPI_Finalize();

  return 0;
}
