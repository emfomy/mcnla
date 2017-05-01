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

  magma_print_environment();

  int n = 10;

  mcnla::matrix::DenseVector<double> a(n), b(n);
  mcnla::matrix::GpuArray<double> da(n), db(n);

  int i = 0;
  for ( auto &v : a ) {
    v = ++i;
  }
  for ( auto &v : b ) {
    v = 0;
  }

  disp(a);
  disp(b);

  magma_dsetmatrix(n, 1, a.valPtr(), n, *da, n);
  magma_dcopy(n, *da, 1, *db, 1);
  magma_dgetmatrix(n, 1, *db, n, b.valPtr(), n);

  disp(a);
  disp(b);

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

//   mcnla::index_t m = 11, n = 20, k = 3, p = 1, Nj = 2;

//   mcnla::isvd::Parameters<double> parameters(mpi_root, mpi_comm);
//   parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
//   parameters.sync();

//   mcnla::matrix::DenseMatrixColMajor<double> a(m, n);
//   mcnla::random::Streams streams(0);
//   mcnla::random::gaussian(streams, a.vectorize());
//   mcnla::mpi::bcast(a, mpi_root, mpi_comm);

//   auto aj    = a(parameters.rowrange(), ""_);
//   auto qi    = parameters.createCollectionQ();
//   auto qij   = parameters.createCollectionQj();
//   auto qbar  = parameters.createMatrixQ();
//   auto qbarj = parameters.createMatrixQj();

//   mcnla::isvd::RowBlockGaussianProjectionSketcher<double> sketcher(parameters, 0);
//   mcnla::isvd::PolarOrthogonalizer<double> orthogonalizer(parameters);
//   mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
//   mcnla::isvd::PolarFormer<double> former(parameters);
//   sketcher.initialize();
//   orthogonalizer.initialize();
//   integrator.initialize();
//   former.initialize();

//   mcnla::isvd::CollectionFromRowBlockConverter<double> so_converter(parameters);
//   mcnla::isvd::CollectionToRowBlockConverter<double> oi_converter(parameters);
//   mcnla::isvd::MatrixFromRowBlockConverter<double> if_converter(parameters);
//   so_converter.initialize();
//   oi_converter.initialize();
//   if_converter.initialize();

//   if ( mpi_rank == mpi_root ) {
//     std::cout << "Uses " << sketcher << "." << std::endl;
//     std::cout << "Uses " << orthogonalizer << "." << std::endl;
//     std::cout << "Uses " << integrator << "." << std::endl;
//     std::cout << "Uses " << former << "." << std::endl << std::endl;
//   }

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

  mcnla::finalize();

  return 0;
}
