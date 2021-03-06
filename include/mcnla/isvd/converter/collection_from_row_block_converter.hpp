////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_from_row_block_converter.hpp
/// @brief   The converter that converts collection Q from row-block storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/collection_from_row_block_converter.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS Converter<CollectionFromRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS CollectionFromRowBlockConverter<_Val>
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
/// @param  collection_q   The matrix collection Q.
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q
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

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));
  mcnla_assert_eq(collection_q.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch_each));

  auto matrix_qs_full = collection_q.unfold();
  matrix_qs_full.resize(nrow_total, ""_);

  DenseMatrixCollectionColBlockRowMajor<_Val> collection_qj_tmp(dim_sketch_each, collection_qj.unfold());
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_q_tmp(nrow_rank, nrow_each, matrix_qs_full);

  double comm_moment, comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Start

  // Rearrange Qj
  for ( auto j = 0; j < mpi_size; ++j ) {
    la::copy(collection_qj_tmp(j), collection_q_tmp(j));
  }

  // Exchange Q
  comm_moment = utility::getTime();
  mpi::alltoall(matrix_qs_full, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HPP_
