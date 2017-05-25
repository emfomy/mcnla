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
  install(TARGETS ${target} RUNTIME DESTINATION ${BIN_FOLDER})
endmacro()

# Set target (isvd_dense)
set_target(isvd_dense isvd_dense.cpp)

# Set target (isvd)
add_custom_target(
  isvd
  DEPENDS isvd_dense
)
