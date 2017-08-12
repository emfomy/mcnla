# The CMake setting of 'report/'

# Break
if(NOT MCNLA_BUILD_REPOET)
  return()
endif()

# Disable asserts
list(APPEND DEFS "NDEBUG")

# Add reports
include(report.cmake)

# CPU reports
set(DEFS_TMP "${DEFS}")
list(REMOVE_ITEM DEFS "MCNLA_USE_GPU")

# Sketcher
add_report(sketcher row_block_gaussian_projection_sketcher)
add_report(sketcher col_block_gaussian_projection_sketcher)

# Integrator
add_report(integrator kolmogorov_nagumo_integrator)
add_report(integrator row_block_kolmogorov_nagumo_integrator)
add_report(integrator row_block_gramian_kolmogorov_nagumo_integrator)
add_report(integrator row_block_wen_yin_integrator)
add_report(integrator row_block_gramian_wen_yin_integrator)
add_report(integrator row_block_reduction_integrator)

set(DEFS "${DEFS_TMP}")
unset(DEFS_TMP)

# GPU tests
if(MCNLA_USE_GPU)
  # Sketcher
  add_report(sketcher row_block_gaussian_projection_sketcher_gpu)
  add_report(sketcher col_block_gaussian_projection_sketcher_gpu)
endif()

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
