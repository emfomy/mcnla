////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_q_from_rowblock_converter.hpp
/// @brief   The converter that converts collection Q from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/collection_q_from_rowblock_converter.hh>
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
Converter<CollectionQFromRowBlockConverterTag, _Val>::Converter(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Converter<CollectionQFromRowBlockConverterTag, _Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  collection_q   The matrix collection Q.
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Converter<CollectionQFromRowBlockConverterTag, _Val>::runImpl(
    DenseMatrixCollection201<ValType> &collection_qj,
    DenseMatrixCollection201<ValType> &collection_q
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.nrow();
  const auto nrow_total      = parameters_.nrowTotal();
  const auto nrow_each       = parameters_.nrowEach();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_each, dim_sketch, num_sketch));
  mcnla_assert_eq(collection_q.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch_each));

  auto matrix_qs_full = collection_q.unfold();
  matrix_qs_full.resize(nrow_total, matrix_qs_full.ncol());

  moments_.emplace_back(MPI_Wtime());  // start

  // Rearrange Qj
  for ( auto j = 0; j < mpi_size; ++j ) {
    la::copy(collection_qj(IdxRange{j, j+1} * num_sketch_each).unfold(), matrix_qs_full(IdxRange{j, j+1} * nrow_each, ""))  ;
  }

  // Exchange Q
  mpi::alltoall(matrix_qs_full, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HPP_
