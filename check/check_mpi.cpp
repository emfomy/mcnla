#include <iostream>
#include <gtest/gtest.h>
#include <mpi.h>
#include <mcnla.hpp>

int main( int argc, char **argv ) {
  MPI_Init(&argc, &argv);

  if ( ! mcnla::mpi::isCommRoot(0, MPI_COMM_WORLD) ) {
    fclose(stdout);
  }

  std::cout << "MCNLA "
            << MCNLA_VERSION_MAJOR << "."
            << MCNLA_VERSION_MINOR << "."
            << MCNLA_VERSION_PATCH << " "
            << MCNLA_CHECK_NAME << std::endl << std::endl;

  std::cout << "Using " << mcnla::mpi::getCommSize(MPI_COMM_WORLD) << " MPI nodes." << std::endl << std::endl;

  testing::InitGoogleTest(&argc, argv);
  auto retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  MPI_Finalize();
  return retval;
}
