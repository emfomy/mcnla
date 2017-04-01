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
#include <mcnla/core/random.hpp>

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
class Parameters {

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

  /// The tag shows if the parameter is synchronized.
  bool synchronized_ = false;

  /// The random streams.
  random::Streams streams_;

  /// The sub-parameters.
  struct {
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
  } params_;

 public:

  // Constructors
  inline Parameters( const MPI_Comm mpi_comm, const mpi_int_t mpi_root, const index_t seed = rand() ) noexcept;

  // Synchronize
  inline void sync() noexcept;

  // Gets parameter
  inline bool isSynchronized() const noexcept;
  inline index_t nrow() const noexcept;
  inline index_t nrowEach() const noexcept;
  inline index_t nrowTotal() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t rank() const noexcept;
  inline index_t overRank() const noexcept;
  inline index_t dimSketch() const noexcept;
  inline index_t numSketch() const noexcept;
  inline index_t numSketchEach() const noexcept;
  inline const random::Streams& streams() const noexcept;

  // Sets parameter
  template <class _Matrix>
  inline Parameters& setSize( const _Matrix &matrix ) noexcept;
  inline Parameters& setSize( const index_t nrow, const index_t ncol ) noexcept;
  inline Parameters& setRank( const index_t rank ) noexcept;
  inline Parameters& setOverRank( const index_t over_rank ) noexcept;
  inline Parameters& setNumSketch( const index_t num_sketch ) noexcept;
  inline Parameters& setNumSketchEach( const index_t num_sketch_each ) noexcept;
  inline Parameters& setSeed( const index_t seed ) noexcept;
  inline Parameters& setSeeds( const index_t seed ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_PARAMETERS_HH_
