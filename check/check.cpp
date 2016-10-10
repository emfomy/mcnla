#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <mcnla.hpp>

int main() {
  std::cout << "MCNLA "
            << MCNLA_VERSION_MAJOR << "."
            << MCNLA_VERSION_MINOR << "."
            << MCNLA_VERSION_PATCH << " "
            << MCNLA_CHECK_NAME << std::endl << std::endl;

  CppUnit::TextUi::TestRunner runner;
  CppUnit::BriefTestProgressListener linster;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry("DenseMatrix").makeTest());
  runner.eventManager().addListener(&linster);
  runner.run("", false, true, false);
  return 0;
}
