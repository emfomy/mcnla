# Create configure files
file(
  GLOB_RECURSE configfiles
  RELATIVE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*.in"
)
foreach(configfile ${configfiles})
  string(REGEX REPLACE "\\.[^.]*$" "" file ${configfile})
  configure_file(
    "${PROJECT_SOURCE_DIR}/${configfile}"
    "${PROJECT_BINARY_DIR}/${file}"
  )
endforeach()
