# The CMake setting of 'doxygen/'

# DOxygen
find_package(Doxygen REQUIRED)

# Set documentation directory
set(MCNLA_DOCS_DIR "${PROJECT_BINARY_DIR}/docs")
set(MCNLA_DOCS_DIR "${MCNLA_DOCS_DIR}" PARENT_SCOPE)

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
  "${MCNLA_DOCS_DIR}"
)
