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
template <typename _Val>
Parameters<_Val>::Parameters( const MPI_Comm mpi_comm ) noexcept
  : mpi_size_(mcnla::mpi::commSize(mpi_comm)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the driver is initialized.
///
template <typename _Val>
bool Parameters<_Val>::isInitialized() const noexcept {
  return initialized_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the driver is computed.
///
template <typename _Val>
bool Parameters<_Val>::isComputed() const noexcept {
  return computed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix.
///
template <typename _Val>
index_t Parameters<_Val>::nrow() const noexcept {
  return nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of column of the matrix.
///
template <typename _Val>
index_t Parameters<_Val>::ncol() const noexcept {
  return ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the desired rank of approximate SVD.
///
template <typename _Val>
index_t Parameters<_Val>::rank() const noexcept {
  return rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the oversampling dimension.
///
template <typename _Val>
index_t Parameters<_Val>::overRank() const noexcept {
  return over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimension of random sketches.
///
template <typename _Val>
index_t Parameters<_Val>::dimSketch() const noexcept {
  return rank_ + over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches of all MPI nodes.
///
template <typename _Val>
index_t Parameters<_Val>::numSketch() const noexcept {
  return num_sketch_each_ * mpi_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches per MPI node.
///
template <typename _Val>
index_t Parameters<_Val>::numSketchEach() const noexcept {
  return num_sketch_each_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum iteration
///
template <typename _Val>
index_t Parameters<_Val>::maxIteration() const noexcept {
  return max_iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of converge condition.
///
template <typename _Val>
RealValT<_Val> Parameters<_Val>::tolerance() const noexcept {
  return tolerance_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_PARAMETERS_HPP_