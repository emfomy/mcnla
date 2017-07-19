////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/col_block_gaussian_projection_sketcher_gpu.cpp
/// @brief   The report for Gaussian projection sketcher with GPU support (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

using ValType = double;
#define Stage ColBlockGaussianProjectionSketcherGpu

#include "../../include/sketcher/col_block_sketcher.hpp"

const mcnla::index_t seed = 0;

void dispParam() noexcept {
  std::cout << "seed = " << seed << std::endl;
}

void setStage( StageType &sketcher ) noexcept {
  sketcher.setSeed(seed);
}
