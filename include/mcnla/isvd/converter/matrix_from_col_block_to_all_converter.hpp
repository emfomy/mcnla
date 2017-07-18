////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_col_block_to_all_converter.hpp
/// @brief   The converter that converts a matrix from col-block storage to all MPI node.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HPP_

#include <mcnla/isvd/converter/matrix_from_col_block_to_all_converter.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS Converter<MatrixFromColBlockToAllConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS MatrixFromColBlockToAllConverter<_Val>
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
/// @param  matrix_j  The matrix (j-th col-block, where j is the MPI rank).
/// @param  matrix    The matrix.
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    const DenseMatrixColMajor<_Val> &matrix_j,
          DenseMatrixColMajor<_Val> &matrix
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto ncol       = parameters_.ncol();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();

  static_cast<void>(ncol);
  static_cast<void>(ncol_rank);

  mcnla_assert_eq(matrix_j.nrow(), matrix.nrow());
  mcnla_assert_eq(matrix_j.ncol(), ncol_rank);
  mcnla_assert_eq(matrix.ncol(),   ncol);

  auto matrix_j_full = matrix_j;
  matrix_j_full.resize(""_, ncol_each);
  auto matrix_full = matrix;
  matrix_full.resize(""_, ncol_total);

  double comm_moment, comm_time;
  this->tic(comm_time);
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

#undef MCNLA_ALIAS

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HPP_
