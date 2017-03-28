# The CMake setting of 'src/'

# Break
if(NOT MCNLA_BUILD_DEMO)
  return()
endif()

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
