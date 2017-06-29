////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/row_block_gramian_wen_yin_integrator.cpp
/// @brief   The report for Gramian Wen-Yin line search integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage RowBlockGramianWenYinIntegrator

#include "../../include/integrator/row_block_integrator.hpp"

const double tol = 0;
const int maxiter = 16;

void dispParam() noexcept {
  std::cout << "tol = " << tol << ", maxiter = " << maxiter << std::endl;
}

void setStage( StageType &integrator ) noexcept {
  integrator.setMaxIteration(maxiter).setTolerance(0);
}
