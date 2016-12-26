////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/parameters.ipp
/// @brief   The implementation of the parameter structure of iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_PARAMETERS_IPP_
#define MCNLA_ISVD_PARAMETERS_IPP_

#include <mcnla/isvd/parameters.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor
///
template <typename _Scalar>
Parameters<_Scalar>::Parameters( const MPI_Comm comm, const mpi_int_t root ) noexcept
  : mpi_comm(comm),
    mpi_size(mpi::getCommSize(comm)),
    mpi_root(root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the solver is initialized.
///
template <typename _Scalar>
bool Parameters<_Scalar>::isInitialized() const noexcept { return initialized_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the solver is computed.
///
template <typename _Scalar>
bool Parameters<_Scalar>::isComputed() const noexcept { return computed_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::nrow() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of column of the matrix.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::ncol() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the desired rank of approximate SVD.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::getRank() const noexcept { return rank_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the oversampling dimension.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::getOverRank() const noexcept { return over_rank_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimension of random sketches.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::dimSketch() const noexcept { return rank_ + over_rank_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches of all MPI nodes.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::nvecumSketch() const noexcept { return num_sketch_each_ * mpi_size; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches per MPI node.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::nvecumSketchEach() const noexcept { return num_sketch_each_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum iteration
///
template <typename _Scalar>
index_t Parameters<_Scalar>::getMaxIteration() const noexcept { return max_iteration_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of converge condition.
///
template <typename _Scalar>
typename Parameters<_Scalar>::RealScalar Parameters<_Scalar>::getTolerance() const noexcept { return tolerance_; }

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_PARAMETERS_IPP_
