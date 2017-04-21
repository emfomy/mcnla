////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/integrator/integrator.hpp
/// @brief   The definition for integrator report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_INTEGRATOR_INTEGRATOR_HPP_
#define MCNLA_REPORT_INTEGRATOR_INTEGRATOR_HPP_

void setParam( mcnla::isvd::Parameters<double> &parameters, int &num_test, int &skip_test, int argc, char **argv ) noexcept {
  int argi = 0;
  mcnla::index_t Nj = ( argc > ++argi ) ? atof(argv[argi]) : 1;
  mcnla::index_t m  = ( argc > ++argi ) ? atof(argv[argi]) : 1000;
  mcnla::index_t k  = ( argc > ++argi ) ? atof(argv[argi]) : 100;
  num_test          = ( argc > ++argi ) ? atof(argv[argi]) : 10;
  skip_test         = ( argc > ++argi ) ? atof(argv[argi]) : 5;
  parameters.setSize(m, m).setRank(k).setOverRank(0).setNumSketchEach(Nj);
}

#endif  // MCNLA_REPORT_INTEGRATOR_INTEGRATOR_HPP_
