////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/row_block_gramian_kolmogorov_nagumo_integrator.cpp
/// @brief   The report for Gramian Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage RowBlockGramianKolmogorovNagumoIntegrator

#include "../../include/integrator/row_block_integrator.hpp"

const double tol = 0;
const int maxiter = 16;

void dispParam() noexcept {
  std::cout << "tol = " << tol << ", maxiter = " << maxiter << std::endl;
}

void setStage( StageType &integrator ) noexcept {
  integrator.setMaxIteration(maxiter).setTolerance(0);
}
