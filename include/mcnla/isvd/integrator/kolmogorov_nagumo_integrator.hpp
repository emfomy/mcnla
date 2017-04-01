////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

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
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Val  The value type.
///
/// @param   parameters     The parameters.
/// @param   collection_q   The matrix collection Q.
/// @param   matrix_qbar    The matrix Qbar.
/// @param   iteration      The iteration.
/// @param   time2c         The time of communication in iteration.
/// @param   max_iteration  The maximum iteration.
/// @param   tolerance      The tolerance.
///
template <typename _Val>
std::vector<double> kolmogorovNagumoIntegrator(
    const Parameters &parameters,
    const DenseMatrixCollection120<_Val> &collection_q,
          DenseMatrixRowMajor<_Val> &matrix_qbar,
          index_t &iteration,
          double &time2c,
    const index_t max_iteration = 256,
    const RealValT<_Val> tolerance = 1e-4
) noexcept {

  // Parameters
  const auto mpi_comm        = parameters.mpi_comm;
  const auto mpi_root        = parameters.mpi_root;
  const auto nrow            = parameters.nrow();
  const auto nrow_total      = parameters.nrowTotal();
  const auto num_sketch      = parameters.numSketch();
  const auto num_sketch_each = parameters.numSketchEach();
  const auto dim_sketch      = parameters.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));
  matrix_qbar.resize(nrow, dim_sketch);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // The matrix Qs.
  auto &matrix_qs = collection_q.unfold();

  // The matrix Qc.
  auto &matrix_qc = matrix_qbar;

  // The matrix Bs.
  DenseMatrixRowMajor<_Val> matrix_bs(dim_sketch, dim_sketch * num_sketch_each);

  // The matrix D.
  DenseMatrixRowMajor<_Val> matrix_d(dim_sketch, dim_sketch);

  // The matrix Z.
  DenseMatrixRowMajor<_Val> matrix_z(dim_sketch, dim_sketch);

  // The matrix C.
  DenseMatrixRowMajor<_Val> matrix_c(dim_sketch, dim_sketch);

  // The matrix X.
  DenseMatrixRowMajor<_Val> matrix_x(nrow, dim_sketch);

  // The temporary matrix.
  DenseMatrixRowMajor<_Val> matrix_tmp(nrow, dim_sketch);

  // The vector E.
  DenseVector<_Val> vector_e(dim_sketch);

  // The vector F.
  DenseVector<_Val> vector_f(dim_sketch);

  // The SYEV engine.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<_Val>, 'V'> syev_driver(dim_sketch);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  double moment0 = MPI_Wtime();  // rearrangeing Q

  // Broadcast Q0 to Qc
  if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
    la::copy(collection_q(0), matrix_qc);
  }
  mpi::bcast(matrix_qc, mpi_root, mpi_comm);

  double moment1 = MPI_Wtime();

  time2c = 0;

  bool is_converged = false;
  for ( iteration = 0; iteration < max_iteration && !is_converged; ++iteration ) {
    double moment2c;

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bs := sum( Qc' * Qs )
    la::mm(matrix_qc.t(), matrix_qs, matrix_bs);

    // D := Bs * Bs'
    la::rk(matrix_bs, matrix_d.viewSymmetric());

    // X := 1/N * Qs * Bs'
    la::mm(matrix_qs, matrix_bs.t(), matrix_x, 1.0/num_sketch);

    // X -= 1/N * Qc * D
    la::mm(matrix_qc, matrix_d.viewSymmetric(), matrix_x, -1.0/num_sketch, 1.0);

    // Reduce sum X
    moment2c = MPI_Wtime();
    mpi::allreduce(matrix_x, MPI_SUM, mpi_comm);
    time2c += MPI_Wtime() - moment2c;

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(X' * X)
    la::rk(matrix_x.t(), matrix_z.viewSymmetric());

    // Compute the eigen-decomposition of Z -> Z' * E * Z
    syev_driver(matrix_z.viewSymmetric(), vector_e);

    // E := sqrt( I/2 - sqrt( I/4 - E ) )
    vector_e.val().valarray() = std::sqrt(0.5 + std::sqrt(0.25 - vector_e.val().valarray()));

    // F := sqrt( E )
    vector_f.val().valarray() = std::sqrt(vector_e.val().valarray());

    // D := F * Z
    la::mm(vector_f.viewDiagonal(), matrix_z, matrix_d);

    // Z := F \ Z
    la::sm(vector_f.viewDiagonal().inv(), matrix_z);

    // C := D' * D
    la::rk(matrix_d.t(), matrix_c.viewSymmetric());

    // inv(C) := Z' * Z
    la::rk(matrix_z.t(), matrix_d.viewSymmetric());

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qc *= C
    la::copy(matrix_qc.vectorize(), matrix_tmp.vectorize());
    la::mm(matrix_tmp, matrix_c.viewSymmetric(), matrix_qc);

    // Qc += X * inv(C)
    la::mm(matrix_x, matrix_d.viewSymmetric(), matrix_qc, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    vector_e.val().valarray() -= 1.0;
    is_converged = !(la::nrm2(vector_e) / std::sqrt(dim_sketch) > tolerance);
  }

  double moment2 = MPI_Wtime();

  double moment3 = MPI_Wtime();

  return {moment0, moment1, moment2, moment3};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
