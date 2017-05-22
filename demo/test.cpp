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
#ifdef MCNLA_USE_OMP
              << omp_get_max_threads()
#else  //MCNLA_USE_OMP
              << 1
#endif  // MCNLA_USE_OMP
              << " threads per node" << std::endl << std::endl;

    magma_print_environment();
  }

  mcnla::index_t m = 10000, n = 100000, k = 100, p = 1, Nj = 2;

  mcnla::isvd::Parameters<double> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  mcnla::matrix::DenseMatrixRowMajor<double> a(m, n);
  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vectorize());
  mcnla::mpi::bcast(a, mpi_root, mpi_comm);

  auto qi = parameters.createCollectionQ();

  mcnla::matrix::DenseMatrixGpuRowMajor<double> da(a.sizes());
  mcnla::matrix::DenseMatrixCollection201Gpu<double> dqi(qi.sizes());

  mcnla::isvd::GaussianProjectionSketcherGpu<double> sketcher(parameters, 0);
  // mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters, 0);
  sketcher.initialize();

  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
//     std::cout << "Uses " << orthogonalizer << "." << std::endl;
//     std::cout << "Uses " << integrator << "." << std::endl;
//     std::cout << "Uses " << former << "." << std::endl << std::endl;
  }


  magma_dsetmatrix(a.dim0(), a.dim1(), a.valPtr(), a.pitch(), da.valPtr(), da.pitch());
  sketcher(da, dqi);
  auto &qs  = qi.unfold();
  auto &dqs = dqi.unfold();
  magma_dgetmatrix(qs.dim0(), qs.dim1(), dqs.valPtr(), dqs.pitch(), qs.valPtr(), qs.pitch());
  // sketcher(a, qi);

  disp(sketcher.times()[0]);
  disp(sketcher.times()[1]);

  mcnla::finalize();

//   sketcher(aj, qij);
//   so_converter(qij, qi);
//   orthogonalizer(qi);
//   oi_converter(qi, qij);
//   integrator(qij, qbarj);
//   if_converter(qbarj, qbar);
//   former(a, qbar);

//   if ( mpi_rank == mpi_root ) {
//     auto &u = former.matrixU();

//     disp(a);
//     disp(u);

//     mcnla::matrix::DenseMatrixColMajor<double> utu(k, k), uut(m, m);
//     mcnla::la::mm(u.t(), u, utu);
//     mcnla::la::mm(u, u.t(), uut);

//     disp(utu);
//     disp(uut);
//   }

  return 0;
}
