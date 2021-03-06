////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/integrator/naive_integrator.hpp
/// @brief   The definition for naive paralleled integrator report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_INTEGRATOR_NAIVE_INTEGRATOR_HPP_
#define MCNLA_REPORT_INTEGRATOR_NAIVE_INTEGRATOR_HPP_

#include <mcnla.hpp>

struct Data {
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> collection_q;
  mcnla::matrix::DenseMatrixRowMajor<ValType> matrix_q;

  Data( const mcnla::isvd::Parameters<ValType> &parameters ) noexcept
    : collection_q(parameters.createCollectionQ()),
      matrix_q(parameters.createMatrixQbar()) {
    mcnla::random::Streams streams(0);
    mcnla::random::gaussian(streams, collection_q.unfold().vec());
    mcnla::isvd::GramianOrthogonalizer<ValType> orthogonalizer(parameters);
    orthogonalizer.initialize();
    orthogonalizer(collection_q);
  }
};

#include "../stage.hpp"
#include "integrator.hpp"

void runStage( StageType &integrator, Data &data ) noexcept {
  integrator(data.collection_q, data.matrix_q);
}

#endif  // MCNLA_REPORT_INTEGRATOR_NAIVE_INTEGRATOR_HPP_
