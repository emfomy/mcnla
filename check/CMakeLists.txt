# The CMake setting of 'check/'

# CPPUNIT root
set(CPPUNIT_ROOT "" CACHE PATH "The root path of CppUnit.")

# CPPUNIT include
find_path(CPPUNIT_INCLUDE NAMES cppunit PATHS ${CPPUNIT_ROOT})
if(CPPUNIT_INCLUDE STREQUAL CPPUNIT_INCLUDE-NOTFOUND)
  message(FATAL_ERROR "Could NOT find CppUnit headers.")
endif()
set(INCS ${INCS} "${CPPUNIT_INCLUDE}")
message(STATUS "Found CppUnit headers.")

# CPPUNIT library
find_library(CPPUNIT_LIBRARY NAMES cppunit PATHS ${CPPUNIT_ROOT})
if(CPPUNIT_LIBRARY STREQUAL CPPUNIT_LIBRARY-NOTFOUND)
  message(FATAL_ERROR "Could NOT find CppUnit libraries.")
endif()
set(LIBS ${LIBS} "${CPPUNIT_LIBRARY}")
message(STATUS "Found CppUnit libraries.")

# Add check folders
include(check.cmake)
add_check(core_matrix "Matrix Module test")
add_check(core_blas   "BLAS Module test")

# Add rule 'check'
add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_CHECK_TARGETS}
  COMMENT "Running tests"
)
