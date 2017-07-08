# The CMake setting of 'src/'

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set target
  add_executable(${target} ${files})
  mcnla_set_target(${target})
  target_compile_definitions(${target} PUBLIC ${ARGN})
  install(TARGETS ${target} RUNTIME DESTINATION ${BIN_FOLDER})
endmacro()

# Set target (isvd_dense)
set_target(isvd_dense isvd_dense.cpp)

if(MCNLA_USE_GPU)
  set_target(isvd_dense_gpu isvd_dense.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu")
endif(MCNLA_USE_GPU)

# Set target (isvd)
add_custom_target(
  isvd
  DEPENDS isvd_dense
)
