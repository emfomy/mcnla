# The CMake setting of 'doxygen/'

# DOxygen
find_package(Doxygen REQUIRED)

# Create configure files
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
)

# Add rule
if(NOT CMAKE_BUILD_TYPE STREQUAL "Doc")
  add_custom_target(
    doc
    COMMAND doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    COMMENT "Generating documentation with Doxygen"
  )
else()
  add_custom_target(
    doc ALL
    COMMAND doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    COMMENT "Generating documentation with Doxygen"
  )
endif()

# Add to clean rule
set_directory_properties(
  PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "${CMAKE_BINARY_DIR}/documentation"
)
