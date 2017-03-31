////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hpp
/// @brief   The SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HPP_

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
/// @ingroup  isvd_former_module
/// The SVD former.
///
/// @tparam  _Val     The value type.
/// @tparam  _Matrix  The matrix type.
///
/// @param   parameters  The parameters.
/// @param   matrix_q    The matrix Q.
///
template <typename _Val, class _Matrix>
std::vector<double> svdFormer(
    const Parameters &parameters,
    const _Matrix &matrix_a,
    const DenseMatrixRowMajor<_Val> &matrix_q,
          DenseVector<RealValT<_Val>> &vector_s,
          DenseMatrixColMajor<_Val> &matrix_u,
          DenseMatrixColMajor<_Val> &matrix_vt
) noexcept {

  using RealValType = RealValT<_Val>;

  // Parameters
  const auto nrow       = parameters.nrow();
  const auto ncol       = parameters.ncol();
  const auto dim_sketch = parameters.dimSketch();
  const auto rank       = parameters.rank();

  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));
  vector_s.resize(dim_sketch);;
  matrix_u.resize(nrow, dim_sketch);
  matrix_vt.resize(dim_sketch, ncol);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // The matrix W.
  DenseMatrixColMajor<_Val> matrix_w(dim_sketch, dim_sketch);

  // The empty matrix.
  DenseMatrixColMajor<_Val> matrix_empty;

  // The GESVD driver.
  la::GesvdDriver<DenseMatrixColMajor<_Val>, 'S', 'O'> gesvd_driver(dim_sketch, ncol);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  double moment0 = MPI_Wtime();  // Q' * A

  // Vt := Q' * A
  la::gemm(matrix_q.t(), matrix_a, matrix_vt);

  double moment1 = MPI_Wtime();  // SVD

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver(matrix_vt, vector_s, matrix_w, matrix_empty);

  double moment2 = MPI_Wtime();  // Q * W

  // U := Q * W
  la::gemm(matrix_q, matrix_w, matrix_u);

  double moment3 = MPI_Wtime();  // end

  vector_s.resize(rank);
  matrix_u.resize(nrow, rank);
  matrix_vt.resize(rank, ncol);

  return {moment0, moment1, moment2, moment3};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
