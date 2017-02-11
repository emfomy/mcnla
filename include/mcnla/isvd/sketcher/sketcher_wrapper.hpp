////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_wrapper.hpp
/// @brief   The iSVD sketcher wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_
#define MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_

#include <mcnla/isvd/sketcher/sketcher_wrapper.hh>
#include <vector>
#include <random>
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
/// @brief  Construct with given parameters.
///
template <class _Derived>
SketcherWrapper<_Derived>::SketcherWrapper(
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
void SketcherWrapper<_Derived>::initialize() noexcept {
  this->derived().initializeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Random sketches.
///
template <class _Derived> template <class _Matrix>
void SketcherWrapper<_Derived>::sketch(
    const _Matrix &matrix_a,
          DenseMatrixCollection120<ValType> &collection_q
) noexcept {
  this->derived().sketchImpl(matrix_a, collection_q);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output name to stream.
///
template <class __Derived>
std::ostream& operator<< (
    std::ostream &os,
    const SketcherWrapper<__Derived> &wrapper
) {
  return wrapper.outputName(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<
///
template <class _Derived>
std::ostream& SketcherWrapper<_Derived>::outputName(
    std::ostream &os
) const noexcept {
  return this->derived().outputNameImpl(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Driver::sketcherTime
///
template <class _Derived>
double SketcherWrapper<_Derived>::time() const noexcept {
  return this->derived().timeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Driver::setSeed
///
template <class _Derived>
_Derived& SketcherWrapper<_Derived>::setSeed(
    const index_t seed
) noexcept {
  this->derived().setSeedImpl(seed);
  return this->derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Driver::setSeeds
///
template <class _Derived>
_Derived& SketcherWrapper<_Derived>::setSeeds(
    const index_t seed
) noexcept {
  std::vector<index_t> seeds(mpi::commSize(mpi_comm_));
  if ( mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    std::seed_seq seq{seed};
    seq.generate(seeds.begin(), seeds.end());
  }
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp;
  MPI_Scatter(seeds.data(), 1, datatype, &seed_tmp, 1, datatype, mpi_root_, mpi_comm_);
  setSeed(seed_tmp);
  return this->derived();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_
