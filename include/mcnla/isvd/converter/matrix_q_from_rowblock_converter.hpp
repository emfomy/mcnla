////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_q_from_rowblock_converter.hpp
/// @brief   The converter that converts matrix Q from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HPP_

#include <mcnla/isvd/converter/matrix_q_from_rowblock_converter.hh>
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
MatrixQFromRowBlockConverter<_Val>::MatrixQFromRowBlockConverter(
    const Parameters &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void MatrixQFromRowBlockConverter<_Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  matrix_qj  The matrix matrix Qj.
/// @param  matrix_q   The matrix matrix Q.
///
template <typename _Val>
void MatrixQFromRowBlockConverter<_Val>::runImpl(
    DenseMatrixRowMajor<ValType> &matrix_qj,
    DenseMatrixRowMajor<ValType> &matrix_q
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_root        = parameters_.mpi_root;
  const auto nrow            = parameters_.nrow();
  const auto nrow_total      = parameters_.nrowTotal();
  const auto nrow_each       = parameters_.nrowEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_each, dim_sketch));
  mcnla_assert_eq(matrix_q.sizes(),  std::make_tuple(nrow, dim_sketch));

  auto matrix_q_full = matrix_q;
  matrix_q_full.resize(nrow_total, matrix_q_full.ncol());

  moments_.emplace_back(MPI_Wtime());  // start

  // Gather Qc
  mcnla::mpi::gather(matrix_qj, matrix_q_full, mpi_root, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HPP_
