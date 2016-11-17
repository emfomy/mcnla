# Set install rule
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
