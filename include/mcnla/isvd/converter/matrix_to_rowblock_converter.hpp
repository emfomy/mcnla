////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_to_rowblock_converter.hpp
/// @brief   The converter that converts a matrix to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/matrix_to_rowblock_converter.hh>
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
Converter<MatrixToRowBlockConverterTag, _Val>::Converter(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Converter<MatrixToRowBlockConverterTag, _Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  matrix_q   The matrix.
/// @param  matrix_qj  The matrix (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Converter<MatrixToRowBlockConverterTag, _Val>::runImpl(
    const DenseMatrixRowMajor<ValType> &matrix,
          DenseMatrixRowMajor<ValType> &matrix_j
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow       = parameters_.nrow();
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();

  mcnla_assert_eq(matrix.ncol(),   matrix_j.ncol());
  mcnla_assert_eq(matrix.nrow(),   nrow);
  mcnla_assert_eq(matrix_j.nrow(), nrow_rank);

  auto matrix_full = matrix;
  matrix_full.resize(nrow_total, "");
  auto matrix_j_full = matrix_j;
  matrix_j_full.resize(nrow_each, "");

  moments_.emplace_back(MPI_Wtime());  // start

  // Scatter Qc
  mcnla::mpi::scatter(matrix_full, matrix_j_full, mpi_root, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HPP_
