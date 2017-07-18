////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/bin2bin.cpp
/// @brief   The driver for transpose converting binary file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Display program information
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " driver for transpose converting binary file" << std::endl << std::endl;

  // ====================================================================================================================== //
  // Check input
  if ( argc < 3 ) {
    std::cout << "Usage: " << argv[0] << " <input-bin-file> <output-bin-file> [comment]" << std::endl << std::endl;
    abort();
  }
  disp(argv[3])

  // ====================================================================================================================== //
  // Load/save matrix
  std::cout << "Reading size from " << argv[1] << " ........ " << std::flush;
  mcnla::index_t m, n;
  mcnla::io::loadBinarySize<mcnla::Trans::NORMAL>(m, n, argv[1]);
  std::cout << "Done!" << std::endl;

  mcnla::matrix::DenseMatrixColMajor<double> imat(m, n);
  mcnla::matrix::DenseMatrixRowMajor<double> omat(m, n);

  std::cout << "Reading data from " << argv[1] << " ........ " << std::flush;
  mcnla::io::loadBinary(imat, argv[1]);
  std::cout << "Done!" << std::endl;
  mcnla::la::copy(imat, omat);

  std::cout << "Writing data into " << argv[2] << " ........ " << std::flush;
  mcnla::io::saveBinary(omat, argv[2], argv[3]);
  std::cout << "Done!" << std::endl;

}
