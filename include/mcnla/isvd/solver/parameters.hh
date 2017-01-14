////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver/parameters.hh
/// @brief   The definition of parameter structure of iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_PARAMETERS_HH_
#define MCNLA_ISVD_SOLVER_PARAMETERS_HH_

#include <mcnla/def.hpp>
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

  using RealScalarType = RealScalarT<_Scalar>;

 protected:

#ifdef MCNLA_TEST
 public:
#endif  // MCNLA_TEST

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
  RealScalarType tolerance_ = 1e-4;

  /// The MPI size
  const index_t mpi_size_;

 public:

  // Constructors
  Parameters( const MPI_Comm mpi_comm ) noexcept;

  // Gets parameter
  inline bool isInitialized() const noexcept;
  inline bool isComputed() const noexcept;
  inline index_t nrow() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t rank() const noexcept;
  inline index_t overRank() const noexcept;
  inline index_t dimSketch() const noexcept;
  inline index_t numSketch() const noexcept;
  inline index_t numSketchEach() const noexcept;
  inline index_t maxIteration() const noexcept;
  inline RealScalarType tolerance() const noexcept;
};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_PARAMETERS_HH_
