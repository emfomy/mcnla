////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_row_block_to_all_converter.hpp
/// @brief   The converter that converts a matrix from row-block storage to all MPI node.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/matrix_from_row_block_to_all_converter.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Converter<MatrixFromRowBlockToAllConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP MatrixFromRowBlockToAllConverter<_Val>
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
/// @param  matrix_j  The matrix (j-th row-block, where j is the MPI rank).
/// @param  matrix    The matrix.
///
template <typename _Val>
void MCNLA_TMP::runImpl(
    const DenseMatrixRowMajor<_Val> &matrix_j,
          DenseMatrixRowMajor<_Val> &matrix
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow       = parameters_.nrow();
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();

  static_cast<void>(nrow);
  static_cast<void>(nrow_rank);

  mcnla_assert_eq(matrix_j.ncol(), matrix.ncol());
  mcnla_assert_eq(matrix_j.nrow(), nrow_rank);
  mcnla_assert_eq(matrix.nrow(),   nrow);

  auto matrix_j_full = matrix_j;
  matrix_j_full.resize(nrow_each, ""_);
  auto matrix_full = matrix;
  matrix_full.resize(nrow_total, ""_);

  this->tic(); double comm_moment, comm_time = 0.0;
  // ====================================================================================================================== //
  // Start

  // Gather Qc
  comm_moment = utility::getTime();
  mcnla::mpi::allgather(matrix_j_full, matrix_full, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_CONVERTER_HPP_
