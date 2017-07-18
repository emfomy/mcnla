////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/mtx2bin.cpp
/// @brief   The driver for converting Matrix Market file to binary file.
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
            << MCNLA_PATCH_VERSION << " driver for converting Matrix Market file to binary file" << std::endl << std::endl;

  // ====================================================================================================================== //
  // Check input
  if ( argc < 4 ) {
    std::cout << "Usage: " << argv[0] << " <mtx file> <bin file> <storage major (0/1)> [comment]" << std::endl << std::endl;
    abort();
  }
  disp(argv[4])

  // ====================================================================================================================== //
  // Load/save matrix
  if ( atoi(argv[3]) == 0 ) {
    mcnla::matrix::DenseMatrixColMajor<double> mat;

    std::cout << "Reading data from " << argv[1] << " ........ " << std::flush;
    mcnla::io::loadMatrixMarket(mat, argv[1]);
    std::cout << "Done!" << std::endl;

    std::cout << "Writing data into " << argv[2] << " ........ " << std::flush;
    mcnla::io::saveBinary(mat, argv[2], argv[4]);
    std::cout << "Done!" << std::endl;

  } else {
    mcnla::matrix::DenseMatrixRowMajor<double> mat;

    std::cout << "Reading data from " << argv[1] << " ........ " << std::flush;
    mcnla::io::loadMatrixMarket(mat, argv[1]);
    std::cout << "Done!" << std::endl;

    std::cout << "Writing data into " << argv[2] << " ........ " << std::flush;
    mcnla::io::saveBinary(mat, argv[2], argv[4]);
    std::cout << "Done!" << std::endl;
  }

}
