////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/parameters.hh
/// @brief   The definition of parameter structure of iSVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CORE_PARAMETERS_HH_
#define MCNLA_ISVD_CORE_PARAMETERS_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/core/mpi.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_core_module
/// The parameters of iSVD driver.
///
struct Parameters {

 public:

  /// The MPI communicator
  const MPI_Comm mpi_comm;

  /// The MPI size
  const index_t mpi_size;

  /// The MPI root
  const index_t mpi_root;

  /// The MPI rank
  const index_t mpi_rank;

 protected:

  /// The number of rows of the matrix.
  index_t nrow_ = 0;

  /// The number of columns of the matrix.
  index_t ncol_ = 0;

  /// The desired rank of approximate SVD.
  index_t rank_ = 0;

  /// The oversampling dimension.
  index_t over_rank_ = 12;

  /// The number of random sketches per MPI node.
  index_t num_sketch_each_ = 1;

 public:

  // Constructors
  inline Parameters( const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Boardcast
  inline void sync() noexcept;

  // Gets parameter
  inline index_t  nrow() const noexcept;
  inline index_t  nrowEach() const noexcept;
  inline index_t  nrowTotal() const noexcept;
  inline index_t  ncol() const noexcept;
  inline index_t  rank() const noexcept;
  inline index_t  overRank() const noexcept;
  inline index_t  dimSketch() const noexcept;
  inline index_t  numSketch() const noexcept;
  inline index_t  numSketchEach() const noexcept;

  // Sets parameter
  inline index_t& nrow() noexcept;
  inline index_t& ncol() noexcept;
  inline index_t& rank() noexcept;
  inline index_t& overRank() noexcept;
  inline index_t& numSketchEach() noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_PARAMETERS_HH_
