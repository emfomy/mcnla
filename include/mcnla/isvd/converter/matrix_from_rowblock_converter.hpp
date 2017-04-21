////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_rowblock_converter.hpp
/// @brief   The converter that converts a matrix from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/matrix_from_rowblock_converter.hh>
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
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
Converter<MatrixFromRowBlockConverterTag, _Val>::Converter(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Converter<MatrixFromRowBlockConverterTag, _Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  matrix_j  The matrix (j-th row-block, where j is the MPI rank).
/// @param  matrix    The matrix.
///
template <typename _Val>
void Converter<MatrixFromRowBlockConverterTag, _Val>::runImpl(
    const DenseMatrixRowMajor<ValType> &matrix_j,
          DenseMatrixRowMajor<ValType> &matrix
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow       = parameters_.nrow();
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();

  mcnla_assert_eq(matrix_j.ncol(), matrix.ncol());
  mcnla_assert_eq(matrix_j.nrow(), nrow_rank);
  mcnla_assert_eq(matrix.nrow(),   nrow);

  auto matrix_j_full = matrix_j;
  matrix_j_full.resize(nrow_each, "");
  auto matrix_full = matrix;
  matrix_full.resize(nrow_total, "");

  moments_.emplace_back(MPI_Wtime());  // start

  // Gather Qc
  mcnla::mpi::gather(matrix_j_full, matrix_full, mpi_root, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HPP_