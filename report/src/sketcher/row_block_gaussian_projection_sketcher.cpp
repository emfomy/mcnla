////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/row_block_gaussian_projection_sketcher.cpp
/// @brief   The report for Gaussian projection sketcher (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage RowBlockGaussianProjectionSketcher

#include "../../include/sketcher/row_block_sketcher.hpp"

const mcnla::index_t seed = 0;

void dispParam() noexcept {
  std::cout << "seed = " << seed << std::endl;
}

void setStage( StageType &sketcher ) noexcept {
  sketcher.setSeed(seed);
}
