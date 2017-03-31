////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hpp
/// @brief   The column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_

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
/// The column sampling sketcher.
///
/// @tparam  _Val  The value type.
///
/// @param   parameters    The parameters.
/// @param   matrix_a      The matrix A.
/// @param   collection_q  The matrix collection Q.
/// @param   seed          The random seed.
///
template <typename _Val, class _Matrix>
std::vector<double> sketcherColumnSampling(
    const Parameters &parameters,
    const _Matrix &matrix_a,
          DenseMatrixCollection120<_Val> &collection_q,
    const random::MpiStreams &mpi_streams
) noexcept {

  const auto nrow             = parameters.nrow();
  const auto ncol             = parameters.ncol();
  const auto num_sketch_each  = parameters.numSketchEach();
  const auto dim_sketch       = parameters.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(),     std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  DenseVector<index_t> vector_idxs(dim_sketch * num_sketch_each);

  double moment0 = MPI_Wtime();

  // Random sample Idxs using uniform distribution
  random::uniform(mpi_streams, vector_idxs, 0, ncol);

  double moment1 = MPI_Wtime();

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch_each; ++i ) {
    la::copy(matrix_a("", vector_idxs(i)), collection_q.unfold()("", i));
  }

  double moment2 = MPI_Wtime();

  return {moment0, moment1, moment2};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
