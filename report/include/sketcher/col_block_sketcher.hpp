////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/sketcher/col_block_sketcher.hpp
/// @brief   The definition for column-block sketcher report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_SKETCHER_COL_BLOCK_SKETCHER_HPP_
#define MCNLA_REPORT_SKETCHER_COL_BLOCK_SKETCHER_HPP_

#include <mcnla.hpp>

struct Data {
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_a;
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> collection_qjp;

  Data( const mcnla::isvd::Parameters<ValType> &parameters ) noexcept
    : matrix_a(parameters.nrow(), parameters.ncolRank()),
      collection_qjp(parameters.createCollectionQjp()) {
    mcnla::random::Streams streams(0);
    mcnla::random::gaussian(streams, matrix_a.vec());
  }
};

#include "../stage.hpp"
#include "sketcher.hpp"

void runStage( StageType &sketcher, Data &data ) noexcept {
  sketcher(data.matrix_a, data.collection_qjp);
}

#endif  // MCNLA_REPORT_SKETCHER_COL_BLOCK_SKETCHER_HPP_
