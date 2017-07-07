////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/row_block_reduction_integrator.cpp
/// @brief   The report for reduction integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage RowBlockReductionIntegrator

#include "../../include/integrator/row_block_integrator.hpp"

const double tol = 0;
const int maxiter = 16;

void dispParam() noexcept {}

void setStage( StageType &integrator ) noexcept {
  static_cast<void>(integrator);
}
