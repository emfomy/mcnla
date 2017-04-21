////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/row_block_gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/row_block_gaussian_projection_sketcher.hh>
#include <mcnla/core/la.hpp>
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
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::Sketcher(
    const Parameters<ValType> &parameters,
    const index_t seed,
    const index_t exponent
) noexcept
  : BaseType(parameters) {
  setSeed(seed);
  setExponent(exponent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::initializeImpl() noexcept {

  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  matrix_omegas_.reconstruct(ncol, dim_sketch * num_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_aj      The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::runImpl(
    const _Matrix &matrix_aj,
          DenseMatrixCollection201<ValType> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  mcnla_assert_eq(matrix_aj.sizes(),     std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp = seed_;
  MPI_Bcast(&seed_tmp, 1, datatype, mpi_root, mpi_comm);
  random::Streams streams(seed_tmp);

  moments_.emplace_back(MPI_Wtime());  // random generating

  // Random sample Omega using normal Gaussian distribution
  random::gaussian(streams, matrix_omegas_.vectorize());

  moments_.emplace_back(MPI_Wtime());  // projection

  // Q := A * Omega
  la::mm(matrix_aj, matrix_omegas_, collection_qj.unfold());

  moments_.emplace_back(MPI_Wtime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::outputName
///
///
template <typename _Val>
std::ostream& Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power " << exponent_ << ")");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the exponent of power method.
///
template <typename _Val>
index_t Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::exponent() const noexcept {
  return exponent_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>& Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the exponent of power method.
///
/// @attention  Row-block version supports zero exponent only.
///
template <typename _Val>
Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>& Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>::setExponent(
    const index_t exponent
) noexcept {
  mcnla_assert_eq(exponent, 0);
  exponent_ = exponent;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HPP_
