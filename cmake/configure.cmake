# Create configure files
string(REPLACE ";" " " DEFS_STR "${DEFS}")
unset(cfgfiles)
file(
  GLOB_RECURSE cfgfiles
  RELATIVE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*.in"
)
foreach(cfgfile ${cfgfiles})
  string(REGEX REPLACE "\\.[^.]*$" "" file ${cfgfile})
  configure_file(
    "${PROJECT_SOURCE_DIR}/${cfgfile}"
    "${PROJECT_BINARY_DIR}/${file}"
    @ONLY
  )
endforeach()
