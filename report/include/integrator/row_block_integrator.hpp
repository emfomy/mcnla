////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/integrator/row_block_integrator.hpp
/// @brief   The definition for row-block integrator report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_INTEGRATOR_ROW_BLOCK_INTEGRATOR_HPP_
#define MCNLA_REPORT_INTEGRATOR_ROW_BLOCK_INTEGRATOR_HPP_

#include <mcnla.hpp>

struct Data {
  mcnla::matrix::DenseMatrixCollection201<ValType> collection_qj;
  mcnla::matrix::DenseMatrixRowMajor<ValType> matrix_qj;

  Data( const mcnla::isvd::Parameters<ValType> &parameters ) noexcept
    : collection_qj(parameters.createCollectionQj()),
      matrix_qj(parameters.createMatrixQj()) {
    mcnla::random::Streams streams(0);
    mcnla::random::gaussian(streams, collection_qj.unfold().vec());
    mcnla::isvd::RowBlockGramianOrthogonalizer<ValType> orthogonalizer(parameters);
    orthogonalizer.initialize();
    orthogonalizer(collection_qj);
  }
};

#include "../stage.hpp"
#include "integrator.hpp"

void runStage( StageType &integrator, Data &data ) noexcept {
  integrator(data.collection_qj, data.matrix_qj);
}

#endif  // MCNLA_REPORT_INTEGRATOR_ROW_BLOCK_INTEGRATOR_HPP_
