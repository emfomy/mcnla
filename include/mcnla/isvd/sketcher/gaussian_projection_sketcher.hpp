////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/core/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la.hpp>
#include <mcnla/core/random.hpp>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher.
///
/// @tparam  _Val  The value type.
/// @tparam  _Matrix  The matrix type.
///
/// @param   parameters    The parameters.
/// @param   matrix_a      The matrix A.
/// @param   collection_q  The matrix collection Q.
/// @param   mpi_streams   The MPI random streams.
/// @param   exponent      The exponent of the power method.
///
template <typename _Val, class _Matrix>
std::vector<double> gaussianProjectionSketcher(
    const Parameters &parameters,
    const _Matrix &matrix_a,
          DenseMatrixCollection120<_Val> &collection_q,
    const random::MpiStreams &mpi_streams,
    const index_t exponent = 0
) noexcept {

  // Parameters
  const auto nrow            = parameters.nrow();
  const auto ncol            = parameters.ncol();
  const auto num_sketch_each = parameters.numSketchEach();
  const auto dim_sketch      = parameters.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(),     std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  // The matrix Omegas
  DenseMatrixRowMajor<_Val> matrix_omegas(ncol, dim_sketch * num_sketch_each);

  double moment0 = MPI_Wtime();

  // Random sample Omega using normal Gaussian distribution
  random::gaussian(mpi_streams, matrix_omegas.vectorize());

  double moment1 = MPI_Wtime();

  // Q := A * Omega
  la::mm(matrix_a, matrix_omegas, collection_q.unfold());
  for ( index_t i = 0; i < exponent; ++i ) {
    la::mm(matrix_a.t(), collection_q.unfold(), matrix_omegas);
    la::mm(matrix_a, matrix_omegas, collection_q.unfold());
  }

  double moment2 = MPI_Wtime();

  return {moment0, moment1, moment2};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
