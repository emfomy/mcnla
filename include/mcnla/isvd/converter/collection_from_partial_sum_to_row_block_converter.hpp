////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_from_partial_sum_to_row_block_converter.hpp
/// @brief   The converter that converts collection Q from partial sum to row-block storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/collection_from_partial_sum_to_row_block_converter.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS Converter<CollectionFromPartialSumToRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS CollectionFromPartialSumToRowBlockConverter<_Val>
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
MCNLA_ALIAS::Converter(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_ALIAS::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  collection_qjp  The matrix collection Qjp (j-th partial-sum, where j is the MPI rank).
/// @param  collection_qj   The matrix collection Qj  (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qjp,
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow       = parameters_.nrow();
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  static_cast<void>(num_sketch);

  mcnla_assert_eq(collection_qjp.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  auto matrix_qjp_full = collection_qjp.unfold();
  auto matrix_qj_full = collection_qj.unfold();
  matrix_qjp_full.resize(nrow_total, ""_);
  matrix_qj_full.resize(nrow_each, ""_);

  this->tic(); double comm_moment, comm_time = 0.0;
  // ====================================================================================================================== //
  // Start

  // Exchange Q
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_qjp_full, matrix_qj_full, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);

}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HPP_
