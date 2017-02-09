////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/driver/parameters.hpp
/// @brief   The the parameter structure of iSVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_PARAMETERS_HPP_
#define MCNLA_ISVD_PARAMETERS_HPP_

#include <mcnla/isvd/driver/parameters.hh>

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
Parameters<_Scalar>::Parameters( const MPI_Comm mpi_comm ) noexcept
  : mpi_size_(mcnla::mpi::commSize(mpi_comm)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the driver is initialized.
///
template <typename _Scalar>
bool Parameters<_Scalar>::isInitialized() const noexcept {
  return initialized_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the driver is computed.
///
template <typename _Scalar>
bool Parameters<_Scalar>::isComputed() const noexcept {
  return computed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::nrow() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of column of the matrix.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::ncol() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the desired rank of approximate SVD.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::rank() const noexcept {
  return rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the oversampling dimension.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::overRank() const noexcept {
  return over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimension of random sketches.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::dimSketch() const noexcept {
  return rank_ + over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches of all MPI nodes.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::numSketch() const noexcept {
  return num_sketch_each_ * mpi_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches per MPI node.
///
template <typename _Scalar>
index_t Parameters<_Scalar>::numSketchEach() const noexcept {
  return num_sketch_each_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum iteration
///
template <typename _Scalar>
index_t Parameters<_Scalar>::maxIteration() const noexcept {
  return max_iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of converge condition.
///
template <typename _Scalar>
RealScalarT<_Scalar> Parameters<_Scalar>::tolerance() const noexcept {
  return tolerance_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_PARAMETERS_HPP_