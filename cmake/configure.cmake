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

# Set install rule
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/lib/"     DESTINATION lib     PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/lib/"     DESTINATION lib     PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/share/"   DESTINATION share   PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/share/"   DESTINATION share   PATTERN "*.in" EXCLUDE)
