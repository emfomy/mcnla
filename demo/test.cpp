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

  MPI_Init(&argc, &argv);

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
#ifdef MCNLA_USE_OMP
              << omp_get_max_threads()
#else  //MCNLA_USE_OMP
              << 1
#endif  // MCNLA_USE_OMP
              << " threads per node" << std::endl << std::endl;
  }

  mcnla::index_t m = 6, n = 10, k = 3, p = 1, Nj = 2, K = mpi_size;

  mcnla::isvd::Parameters<double> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  auto mj = parameters.nrowEach();
  mcnla::matrix::DenseMatrixCollection102<double> a_full(mj, n, K);
  auto a = (a_full.unfold())({0, m}, "");
  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vectorize());
  mcnla::mpi::bcast(a, mpi_root, mpi_comm);

  auto aj    = a_full(mpi_rank);
  auto qij   = parameters.createCollectionQj();
  auto qbar  = parameters.createMatrixQ();
  auto qbarj = parameters.createMatrixQj();

  mcnla::isvd::RowBlockGaussianProjectionSketcher<double> sketcher(parameters, 0);
  mcnla::isvd::RowBlockPolarOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();

  mcnla::isvd::MatrixQFromRowBlockConverter<double> if_converter(parameters);
  if_converter.initialize();

  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  sketcher(aj, qij);;
  orthogonalizer(qij);
  integrator(qij, qbarj);
  if_converter(qbarj, qbar);
  former(a, qbar);

  if ( mpi_rank == mpi_root ) {
    auto &u = former.matrixU();

    disp(a);
    disp(qbar);
    disp(u);

    mcnla::matrix::DenseMatrixColMajor<double> utu(k, k), uut(m, m);
    mcnla::la::mm(u.t(), u, utu);
    mcnla::la::mm(u, u.t(), uut);

    disp(utu);
    disp(uut);
  }

  MPI_Finalize();

  return 0;
}
