#include <iostream>
#include <gtest/gtest.h>
#include <mcnla.hpp>

int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_VERSION_MAJOR << "."
            << MCNLA_VERSION_MINOR << "."
            << MCNLA_VERSION_PATCH << " "
            << MCNLA_CHECK_NAME << std::endl << std::endl;

  testing::InitGoogleTest(&argc, argv);
  auto retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);
  return retval;
}
