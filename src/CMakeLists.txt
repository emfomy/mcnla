# The CMake setting of 'src/'

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Macro
macro(SET_TARGET target files)
  # Set target
  add_executable(${target} ${files})
  target_include_directories(${target} PUBLIC "${PROJECT_BINARY_DIR}/include")
  target_include_directories(${target} PUBLIC "${PROJECT_SOURCE_DIR}/include")
  target_include_directories(${target} PUBLIC SYSTEM ${INCS})
  target_link_libraries(${target} ${LIBS})
  target_compile_definitions(${target} PUBLIC ${DEFS} ${ARGN})
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})
  install(TARGETS ${target} RUNTIME DESTINATION bin)
endmacro()

# Set target (isvd_dense)
set_target(isvd_dense isvd.cpp "-DATYPE=DenseMatrix")

# Set target (isvd_coo)
set_target(isvd_coo isvd.cpp "-DATYPE=CooMatrix")

# Set target (isvd)
add_custom_target(
  isvd
  DEPENDS isvd_dense isvd_coo
)
