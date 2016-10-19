////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/parameters.hpp
/// @brief   The parameter structure of iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_PARAMETERS_HPP_
#define MCNLA_ISVD_PARAMETERS_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
///
/// The parameters of iSVD solver.
///
/// @tparam  _Scalar  The scalar type type.
///
template <typename _Scalar>
class Parameters {

  template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor> friend class Solver;

 private:

  using RealScalar = RealType<_Scalar>;

 public:

  /// The MPI communicator.
  const MPI_Comm mpi_comm;

  /// The MPI size.
  const mpi_int_t mpi_size;

  /// The MPI root.
  const mpi_int_t mpi_root;

 protected:
#ifdef MCNLA_USE_GTEST
 public:
#endif  // MCNLA_USE_GTEST

  /// The tag shows if the solver is initialized or not.
  bool initialized_ = false;

  /// The tag shows if the solver is computed or not.
  bool computed_ = false;

  /// The number of rows of the matrix.
  index_t nrow_ = 0;

  /// The number of columns of the matrix.
  index_t ncol_ = 0;

  /// The desired rank of approximate SVD.
  index_t rank_ = 0;

  /// The oversampling dimension.
  index_t over_rank_ = 12;

  /// The number of random sketches per MPI node.
  index_t num_sketch_each_ = 0;

  /// The maximum iteration.
  index_t max_iteration_ = 256;

  /// The tolerance of converge condition.
  RealScalar tolerance_ = 1e-4;

 public:

  // Constructors
  Parameters( const MPI_Comm comm, const mpi_int_t root = 0 ) noexcept;

  // Gets parameter
  inline bool isInitialized() const noexcept;
  inline bool isComputed() const noexcept;
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;
  inline index_t getRank() const noexcept;
  inline index_t getOverRank() const noexcept;
  inline index_t getDimSketch() const noexcept;
  inline index_t getNumSketch() const noexcept;
  inline index_t getNumSketchEach() const noexcept;
  inline index_t getMaxIteration() const noexcept;
  inline RealScalar getTolerance() const noexcept;
};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_PARAMETERS_HPP_
