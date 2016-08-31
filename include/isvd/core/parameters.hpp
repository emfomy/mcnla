////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/parameters.hpp
/// @brief   The parameter structure of iSVD solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_PARAMETERS_HPP_
#define ISVD_CORE_PARAMETERS_HPP_

#include <isvd/isvd.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The parameters of iSVD solver.
///
/// @tparam  _RealScalar  The real scalar type type.
///
template <typename _RealScalar>
class Parameters {

  template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor> friend class Solver;

 public:

  /// The MPI communicator.
  const MPI_Comm mpi_comm;

  /// The MPI size.
  const index_t mpi_size;

  /// The MPI rank.
  const index_t mpi_rank;

 protected:

  /// The tag shows if the solver is initialized or not.
  bool is_initialized_ = false;

  /// The number of rows of the matrix.
  index_t nrow_ = 0;

  /// The number of columns of the matrix.
  index_t ncol_ = 0;

  /// The desired rank of approximate SVD.
  index_t rank_ = 0;

  /// The oversampling dimension.
  index_t over_rank_ = 0;

  /// The number of random sketches per MPI node.
  index_t num_sketch_ = 0;

  /// The maximum iteration
  index_t max_iteration_ = 0;

  /// The tolerance for converge condition.
  _RealScalar tolerance_ = 1e-4;

 public:

  // Constructors
  Parameters( const MPI_Comm comm ) noexcept;

  // Gets parameter
  inline bool isInitialized() const noexcept;
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;
  inline index_t getRank() const noexcept;
  inline index_t getOverRank() const noexcept;
  inline index_t getDimSketch() const noexcept;
  inline index_t getNumSketch() const noexcept;
  inline index_t getNumSketchAll() const noexcept;
  inline index_t getMaxIteration() const noexcept;
  inline _RealScalar getTolerance() const noexcept;
};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_PARAMETERS_HPP_
