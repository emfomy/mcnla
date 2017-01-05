////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_wrapper.hpp
/// @brief   The iSVD sketcher wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_
#define MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/solver/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

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
/// The iSVD sketcher wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SketcherWrapper : public utility::CrtpBase<_Derived, SketcherWrapper<_Derived>> {

 public:

  using MatrixAType = typename traits::Traits<_Derived>::MatrixAType;
  using SetYType    = typename traits::Traits<_Derived>::SetYType;
  using ScalarType  = ScalarT<MatrixAType>;

  static_assert(std::is_same<ScalarT<MatrixAType>, ScalarT<SetYType>>::value, "The scalar type does not fit!");

 protected:

  /// @copydoc  mcnla::isvd::Solver::parameters_
  const Parameters<ScalarType> &parameters_;

  /// @copydoc  mcnla::isvd::Solver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Solver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline SketcherWrapper( const Parameters<ScalarType> &parameters,
                          const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Random sketches
  inline void sketch( const MatrixAType &matrix_a, SetYType &set_q ) noexcept;

  // Gets name
  inline constexpr const char* name() const noexcept;

  // Gets compute time
  inline double time() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_
