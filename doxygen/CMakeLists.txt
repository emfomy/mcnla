# The CMake setting of 'doxygen/'

# Create configure files
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
)

# Add rule
add_custom_target(
  doc
  COMMAND doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  COMMENT "Generating documentation with Doxygen"
)

# Add to clean rule
set_directory_properties(
  PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "${CMAKE_BINARY_DIR}/documentation"
)
