////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_base.hpp
/// @brief   The iSVD sketcher interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_
#define MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
///
/// The interface of iSVD sketcher.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SketcherBase : public utility::CrtpBase<_Derived, SketcherBase<_Derived>> {

 public:

  using MatrixType = typename traits::Traits<_Derived>::MatrixType;
  using ScalarType = typename MatrixType::ScalarType;

 protected:

  /// @copydoc  mcnla::isvd::solver::parameters_
  const Parameters<ScalarType> &parameters_;

  /// @copydoc  mcnla::isvd::solver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::solver::mpi_root_
  const mpi_int_t mpi_root_;

  /// @copydoc  mcnla::isvd::solver::seed_
  index_t *seed_;

 protected:

  // Constructor
  inline SketcherBase( const Parameters<ScalarType> &parameters,
                       const MPI_Comm mpi_comm, const mpi_int_t mpi_root, index_t *seed ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Random sketches
  inline void sketch( const MatrixType &matrix_a, DenseMatrixSet120<ScalarType> &set_q ) noexcept;

  // Gets name
  inline constexpr const char* getName() const noexcept;

  // Gets compute time
  inline double getTime() const noexcept;
  inline const std::vector<double> getTimes() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_
