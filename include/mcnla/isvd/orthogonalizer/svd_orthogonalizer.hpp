////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/svd_orthogonalizer.hpp
/// @brief   The SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/core/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la.hpp>
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
/// @ingroup  isvd_orthogonalizer_module
/// The SVD orthogonalizer.
///
/// @tparam  _Val  The value type.
///
/// @param   parameters    The parameters.
/// @param   collection_q  The matrix collection Q.
///
template <typename _Val>
std::vector<double> svdOrthogonalizer(
    const Parameters &parameters,
          DenseMatrixCollection120<_Val> &collection_q
) noexcept {

  using RealValType = RealValT<_Val>;
  using MatrixType  = MatrixT<DenseMatrixCollection120<_Val>>;

  // Parameters
  const auto nrow            = parameters.nrow();
  const auto num_sketch_each = parameters.numSketchEach();
  const auto dim_sketch      = parameters.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // The vector S
  DenseVector<RealValType> vector_s(dim_sketch);

  // The empty matrix
  MatrixType matrix_empty;

  // The GESVD driver.
  la::GesvdDriver<MatrixType, 'O', 'N'> gesvd_driver(nrow, dim_sketch);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  double moment0 = MPI_Wtime();  // orthogonalization

  // Orthogonalizes
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver(collection_q(i), vector_s, matrix_empty, matrix_empty);
  }

  double moment1 = MPI_Wtime();  // end

  return {moment0, moment1};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
