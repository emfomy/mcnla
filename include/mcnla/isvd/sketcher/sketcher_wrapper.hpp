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
    const Parameters &parameters,
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
          DenseMatrixSet120<ScalarType> &set_q
) noexcept {
  this->derived().sketchImpl(matrix_a, set_q);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::sketcherName
///
template <class _Derived>
constexpr const char* SketcherWrapper<_Derived>::name() const noexcept {
  return this->derived().nameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::sketcherTime
///
template <class _Derived>
double SketcherWrapper<_Derived>::time() const noexcept {
  return this->derived().timeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sets the random seed.
///
template <class _Derived>
void SketcherWrapper<_Derived>::setSeed(
    const index_t seed
) noexcept {
  return this->derived().setSeedImpl(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Generate the random seeds and send to each MPI nodes.
///
template <class _Derived>
void SketcherWrapper<_Derived>::setSeeds(
    const index_t seed
) noexcept {
  std::vector<index_t> seeds(mpi::commSize(mpi_comm_));
  if ( mpi::isCommRoot(mpi_comm_, mpi_root_) ) {
    std::seed_seq seq{seed};
    seq.generate(seeds.begin(), seeds.end());
  }
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<index_t>::datatype;
  MPI_Scatter(seeds.data(), 1, datatype, &seed, 1, datatype, mpi_root_, mpi_comm_);
  setSeed(seed);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HPP_
