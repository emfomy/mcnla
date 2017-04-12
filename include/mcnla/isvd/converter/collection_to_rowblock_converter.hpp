////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_to_rowblock_converter.hpp
/// @brief   The converter that converts collection Q to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/collection_to_rowblock_converter.hh>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::ComponentWrapper
///
template <typename _Val>
Converter<CollectionToRowBlockConverterTag, _Val>::Converter(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Converter<CollectionToRowBlockConverterTag, _Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  collection_q   The matrix collection Q.
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Converter<CollectionToRowBlockConverterTag, _Val>::runImpl(
    DenseMatrixCollection201<ValType> &collection_q,
    DenseMatrixCollection201<ValType> &collection_qj
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.nrow();
  const auto nrow_rank       = parameters_.nrowRank();
  const auto nrow_each       = parameters_.nrowEach();
  const auto nrow_total      = parameters_.nrowTotal();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  mcnla_assert_eq(collection_q.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch_each));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  auto matrix_qs_full = collection_q.unfold();
  matrix_qs_full.resize(nrow_total, "");

  DenseMatrixCollection102<ValType> collection_q_tmp(nrow_rank, nrow_each, matrix_qs_full);
  DenseMatrixCollection201<ValType> collection_qj_tmp(dim_sketch * num_sketch_each, collection_qj.unfold());

  moments_.emplace_back(MPI_Wtime());  // start

  // Exchange Q
  mpi::alltoall(matrix_qs_full, mpi_comm);

  // Rearrange Qj
  for ( auto j = 0; j < mpi_size; ++j ) {
    la::copy(collection_q_tmp(j), collection_qj_tmp(j));
  }

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HPP_
