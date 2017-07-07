////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_to_row_block_converter.hpp
/// @brief   The converter that converts collection Q to row-block storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROW_BLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROW_BLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/collection_to_row_block_converter.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Converter<CollectionToRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP CollectionToRowBlockConverter<_Val>
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
MCNLA_TMP::Converter(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_TMP::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  collection_q   The matrix collection Q.
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_TMP::runImpl(
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q,
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.nrow();
  const auto nrow_rank       = parameters_.nrowRank();
  const auto nrow_each       = parameters_.nrowEach();
  const auto nrow_total      = parameters_.nrowTotal();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto dim_sketch_each = parameters_.dimSketchEach();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  static_cast<void>(num_sketch);

  mcnla_assert_eq(collection_q.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch_each));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  auto matrix_qs_full = collection_q.unfold();
  matrix_qs_full.resize(nrow_total, ""_);

  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_q_tmp(nrow_rank, nrow_each, matrix_qs_full);
  DenseMatrixCollectionColBlockRowMajor<_Val> collection_qj_tmp(dim_sketch_each, collection_qj.unfold());

  this->tic(); double comm_moment, comm_time = 0.0;
  // ====================================================================================================================== //
  // Start

  // Exchange Q
  comm_moment = utility::getTime();
  mpi::alltoall(matrix_qs_full, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // Rearrange Qj
  for ( auto j = 0; j < mpi_size; ++j ) {
    la::copy(collection_q_tmp(j), collection_qj_tmp(j));
  }

  this->toc(comm_time);

}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROW_BLOCK_CONVERTER_HPP_
