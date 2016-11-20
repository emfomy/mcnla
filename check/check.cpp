#include <iostream>
#include <gtest/gtest.h>
#include <mcnla.hpp>

int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " "
            << MCNLA_CHECK_NAME << std::endl << std::endl;

  testing::InitGoogleTest(&argc, argv);
  auto retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);
  return retval;
}
