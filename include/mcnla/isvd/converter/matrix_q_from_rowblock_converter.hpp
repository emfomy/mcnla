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
Converter<MatrixQFromRowBlockConverterTag, _Val>::Converter(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Converter<MatrixQFromRowBlockConverterTag, _Val>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts data.
///
/// @param  matrix_qj  The matrix Qj (j-th row-block, where j is the MPI rank).
/// @param  matrix_q   The matrix Q.
///
template <typename _Val>
void Converter<MatrixQFromRowBlockConverterTag, _Val>::runImpl(
    DenseMatrixRowMajor<ValType> &matrix_qj,
    DenseMatrixRowMajor<ValType> &matrix_q
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow       = parameters_.nrow();
  const auto nrow_each  = parameters_.nrowEach();
  const auto dim_sketch = parameters_.dimSketch();
  const auto counts     = parameters_.nrowEachs(dim_sketch);
  const auto displs     = parameters_.rowidxs(dim_sketch);

  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_each, dim_sketch));
  mcnla_assert_eq(matrix_q.sizes(),  std::make_tuple(nrow, dim_sketch));

  moments_.emplace_back(MPI_Wtime());  // start

  // Gather Qc
  mcnla::mpi::gatherv(matrix_qj, matrix_q, counts.data(), displs.data(), mpi_root, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // end

}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HPP_
