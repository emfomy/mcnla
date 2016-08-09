# The CMake setting of 'include/'

# Create configure files
file(
  GLOB_RECURSE configfiles
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.in"
)
foreach(configfile ${configfiles})
  string(REGEX REPLACE "\\.[^.]*$" "" file ${configfile})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${configfile}"
    "${CMAKE_CURRENT_BINARY_DIR}/${file}"
  )
endforeach()
