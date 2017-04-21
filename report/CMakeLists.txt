# The CMake setting of 'report/'

# Break
if(NOT MCNLA_BUILD_REPOET)
  return()
endif()

# Disable asserts
# list(APPEND DEFS "NDEBUG")

# Add reports
include(report.cmake)

add_report(integrator/kolmogorov_nagumo_integrator)
add_report(integrator/row_block_kolmogorov_nagumo_integrator)

# Add rule 'build_report'
add_custom_target(
  build_report
  DEPENDS ${CMAKE_REPORT_TARGETS}
  COMMENT "Building reports"
)

# Add rule 'report'
add_custom_target(
  report
  COMMAND make ${CMAKE_REPORT_RULES}
  DEPENDS build_report
  COMMENT "Running reports"
)
