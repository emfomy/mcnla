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

set_target(isvd_dense_rb_mtx isvd_dense_rb.cpp)
set_target(isvd_dense_rb_bin isvd_dense_rb.cpp "-DFILETYPE=Binary")
set_target(isvd_dense_rb_nv_mtx isvd_dense_rb.cpp "-DNJOBV")
set_target(isvd_dense_rb_nv_bin isvd_dense_rb.cpp "-DFILETYPE=Binary" "-DNJOBV")

set_target(isvd_dense_cb_mtx isvd_dense_cb.cpp)
set_target(isvd_dense_cb_bin isvd_dense_cb.cpp "-DFILETYPE=Binary")
set_target(isvd_dense_cb_nv_mtx isvd_dense_cb.cpp "-DNJOBV")
set_target(isvd_dense_cb_nv_bin isvd_dense_cb.cpp "-DFILETYPE=Binary" "-DNJOBV")

set(DEFS "${DEFS_TMP}")
unset(DEFS_TMP)

# Set GPU target
if(MCNLA_USE_GPU)
  set_target(isvd_dense_rb_mtx_gpu isvd_dense_rb.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu")
  set_target(isvd_dense_rb_bin_gpu isvd_dense_rb.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu" "-DFILETYPE=Binary")
  set_target(isvd_dense_rb_nv_mtx_gpu isvd_dense_rb.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu" "-DNJOBV")
  set_target(isvd_dense_rb_nv_bin_gpu isvd_dense_rb.cpp "-DSTYPE=RowBlockGaussianProjectionSketcherGpu" "-DFILETYPE=Binary" "-DNJOBV")
endif(MCNLA_USE_GPU)

# Set utility target
set_target(mtx2bin mtx2bin.cpp)
