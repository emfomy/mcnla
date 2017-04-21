////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/kolmogorov_nagumo_integrator.cpp
/// @brief   The report for Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage KolmogorovNagumoIntegrator

#include "../include/naive_integrator.hpp"

const double tol = 0;
const int maxiter = 256;

void dispParam() noexcept {
  std::cout << "tol = " << tol << ", maxiter = " << maxiter << std::endl;
}

void setStage( StageType &integrator ) noexcept {
  integrator.setMaxIteration(maxiter).setTolerance(0);
}
