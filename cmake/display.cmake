# Display message
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
message(STATUS "Set 'MCNLA_BUILD_DEMO' to build demo codes.")
message(STATUS "Set 'MCNLA_BUILD_TEST' to build test codes.")
message(STATUS "Set 'MCNLA_BUILD_DOC'  to build documentation.")
message(STATUS "")
message(STATUS "Set 'MCNLA_USE_ILP64' to change the system integer size. (ON: 32bit / OFF: 64bit)")
message(STATUS "Set 'MCNLA_USE_MKL' to enable Intel MKL.")
message(STATUS "Set 'MPI_PROCS' to set the number of MPI processes.")
message(STATUS "")
message(STATUS "Set 'MKL_ROOT'   for the root path of Intel MKL.")
message(STATUS "Set 'GTEST_ROOT' for the root path of Google Test.")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display options
message(STATUS "Build demo codes:     ${MCNLA_BUILD_DEMO}")
message(STATUS "Build test codes:     ${MCNLA_BUILD_TEST}")
message(STATUS "Build documentation:  ${MCNLA_BUILD_DOC}")

message(STATUS "")

message(STATUS "Use MPI:              ${MPI_LIBRARIES}")

if(NOT MCNLA_USE_MKL)
set(LAPACK_LIBS ${LAPACK_LIBRARIES})
list(REMOVE_DUPLICATES LAPACK_LIBS)
message(STATUS "Use BLAS & LAPACK:    ${LAPACK_LIBS}")
else()
message(STATUS "Use BLAS & LAPACK:    OFF")
endif()

if(MCNLA_USE_MKL)
message(STATUS "Use Intel MKL:        ${MKL_ROOT}")
else()
message(STATUS "Use Intel MKL:        OFF")
endif()

if(MCNLA_BUILD_TEST)
message(STATUS "Use Google Test:      ${GTEST_BOTH_LIBRARIES}")
else()
message(STATUS "Use Google Test:      OFF")
endif()

if(MCNLA_BUILD_DOC)
message(STATUS "Use Doxygen:          ${DOXYGEN_EXECUTABLE}")
else()
message(STATUS "Use Doxygen:          OFF")
endif()

message(STATUS "")

if(NOT MCNLA_USE_ILP64)
message(STATUS "System integer size:  32bit (LP64)")
else()
message(STATUS "System integer size:  64bit (ILP64)")
endif()

message(STATUS "MPI processes:        ${MPI_PROCS}")

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
