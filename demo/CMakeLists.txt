# The CMake setting of 'demo/'

# Set target
add_executable(isvd_demo demo.cpp)

# Add rule 'demo'
add_custom_target(
  demo
  COMMAND ./isvd_demo
  DEPENDS isvd_demo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running demo"
)
