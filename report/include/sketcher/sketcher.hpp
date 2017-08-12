////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/sketcher/sketcher.hpp
/// @brief   The definition for sketcher report.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_SKETCHER_SKETCHER_HPP_
#define MCNLA_REPORT_SKETCHER_SKETCHER_HPP_

void setParam( mcnla::isvd::Parameters<double> &parameters, int &num_test, int &skip_test, int argc, char **argv ) noexcept {
  int argi = 0;
  mcnla::index_t N  = ( argc > ++argi ) ? atof(argv[argi]) : 16;
  mcnla::index_t m  = ( argc > ++argi ) ? atof(argv[argi]) : 1000;
  mcnla::index_t n  = ( argc > ++argi ) ? atof(argv[argi]) : 10000;
  mcnla::index_t k  = ( argc > ++argi ) ? atof(argv[argi]) : 100;
  num_test          = ( argc > ++argi ) ? atof(argv[argi]) : 10;
  skip_test         = ( argc > ++argi ) ? atof(argv[argi]) : 5;
  parameters.setSize(m, n).setRank(k).setOverRank(0).setNumSketch(N);
}

#endif  // MCNLA_REPORT_SKETCHER_SKETCHER_HPP_
