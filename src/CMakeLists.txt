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

# Set target
set(DEFS_TMP "${DEFS}")
list(REMOVE_ITEM DEFS "MCNLA_USE_GPU")

set_target(isvd_dense_mtx isvd_dense.cpp)
set_target(isvd_dense_bin isvd_dense.cpp "-DFILETYPE=Binary")

set(DEFS "${DEFS_TMP}")
unset(DEFS_TMP)

# Set GPU target
if(MCNLA_USE_GPU)
  set_target(isvd_dense_mtx_gpu isvd_dense.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu")
  set_target(isvd_dense_bin_gpu isvd_dense.cpp "-DFILETYPE=Binary" "-DSTYPE=RowBlockGaussianProjectionSketcherGpu")
endif(MCNLA_USE_GPU)

# Set utility target
set_target(mtx2bin mtx2bin.cpp)

# Set target (isvd)
add_custom_target(
  isvd
  DEPENDS isvd_dense
)
