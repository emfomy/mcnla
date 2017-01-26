////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/orthogonalizer_wrapper.hpp
/// @brief   The iSVD orthogonalizer wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HPP_

#include <mcnla/isvd/orthogonalizer/orthogonalizer_wrapper.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
OrthogonalizerWrapper<_Derived>::OrthogonalizerWrapper(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : parameters_(parameters),
    mpi_comm_(mpi_comm),
    mpi_root_(mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void OrthogonalizerWrapper<_Derived>::initialize() noexcept {
  this->derived().initializeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Orthogonalizes.
///
template <class _Derived>
void OrthogonalizerWrapper<_Derived>::orthogonalize(
    DenseMatrixCollection120<ScalarType> &collection_q
) noexcept {
  this->derived().orthogonalizeImpl(collection_q);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output name to stream.
///
template <class __Derived>
std::ostream& operator<< (
    std::ostream &os,
    const OrthogonalizerWrapper<__Derived> &wrapper
) {
  return wrapper.outputName(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<
///
template <class _Derived>
std::ostream& OrthogonalizerWrapper<_Derived>::outputName(
    std::ostream &os
) const noexcept {
  return this->derived().outputNameImpl(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Driver::orthogonalizerTime
///
template <class _Derived>
double OrthogonalizerWrapper<_Derived>::time() const noexcept {
  return this->derived().timeImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HPP_
