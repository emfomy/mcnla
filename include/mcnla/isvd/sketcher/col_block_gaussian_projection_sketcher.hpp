////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/col_block_gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/col_block_gaussian_projection_sketcher.hh>
#include <mcnla/core/la.hpp>
#include <mcnla/core/random.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Sketcher<ColBlockGaussianProjectionSketcherTag, _Val>
  #define MCNLA_ALIAS0 Sketcher
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ColBlockGaussianProjectionSketcher<_Val>
  #define MCNLA_ALIAS0 ColBlockGaussianProjectionSketcher
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
MCNLA_ALIAS::MCNLA_ALIAS0(
    const Parameters<_Val> &parameters,
    const index_t seed
) noexcept
  : BaseType(parameters) {
  setSeed(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_ALIAS::initializeImpl() noexcept {

  const auto ncol_rank        = parameters_.ncolRank();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  matrix_omegajs_.reconstruct(ncol_rank, dim_sketch_total);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_ajc      The matrix Ajc (j-th column-block, where j is the MPI rank).
/// @param  collection_qjp  The matrix collection Qjp (j-th partial-sum, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void MCNLA_ALIAS::runImpl(
    const _Matrix &matrix_ajc,
          DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qjp
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow       = parameters_.nrow();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  mcnla_assert_eq(matrix_ajc.sizes(),     std::make_tuple(nrow, ncol_rank));
  mcnla_assert_eq(collection_qjp.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch));

  random::Streams streams(seed_, mpi_root, mpi_comm);

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Random generating

  // Random sample Omega using normal Gaussian distribution
  random::gaussian(streams, matrix_omegajs_.vec());

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  // Q := A * Omega
  la::mm(matrix_ajc, matrix_omegajs_, collection_qjp.unfold());

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::outputName
///
///
template <typename _Val>
std::ostream& MCNLA_ALIAS::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power 0)");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t MCNLA_ALIAS::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
MCNLA_ALIAS& MCNLA_ALIAS::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_
