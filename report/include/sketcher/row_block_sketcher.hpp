////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/sketcher/row_block_sketcher.hpp
/// @brief   The definition for row-block sketcher report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_SKETCHER_ROW_BLOCK_SKETCHER_HPP_
#define MCNLA_REPORT_SKETCHER_ROW_BLOCK_SKETCHER_HPP_

#include <mcnla.hpp>

struct Data {
  mcnla::matrix::DenseMatrixRowMajor<ValType> matrix_a;
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> collection_qj;

  Data( const mcnla::isvd::Parameters<ValType> &parameters ) noexcept
    : matrix_a(parameters.nrowRank(), parameters.ncol()),
      collection_qj(parameters.createCollectionQj()) {
    mcnla::random::Streams streams(0);
    mcnla::random::gaussian(streams, matrix_a.vec());
  }
};

#include "../stage.hpp"
#include "sketcher.hpp"

void runStage( StageType &sketcher, Data &data ) noexcept {
  sketcher(data.matrix_a, data.collection_qj);
}

#endif  // MCNLA_REPORT_SKETCHER_ROW_BLOCK_SKETCHER_HPP_
