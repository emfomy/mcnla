# Display message
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
message(STATUS "Set 'MCNLA_BUILD_DRIVER'  to build driver codes.")
message(STATUS "Set 'MCNLA_BUILD_DEMO'    to build demo codes.")
message(STATUS "Set 'MCNLA_BUILD_REPORT'  to build report codes.")
message(STATUS "Set 'MCNLA_BUILD_TEST'    to build test codes.")
message(STATUS "Set 'MCNLA_BUILD_DOC'     to build documentation.")
message(STATUS "")
# message(STATUS "Set 'MCNLA_USE_GPU'       to enable GPU support.")
message(STATUS "Set 'MCNLA_INT_SIZE'      to select system integer size.")
message(STATUS "Set 'MCNLA_BLAS'          to select BLAS/LAPACK library.")
message(STATUS "Set 'MCNLA_OMP'           to select OpenMP library. (Require Intel MKL)")
message(STATUS "")
message(STATUS "Set 'MKL_ROOT'            for the root path of Intel MKL.")
message(STATUS "Set 'GTEST_ROOT'          for the root path of Google Test.")
message(STATUS "")
message(STATUS "Set 'MPI_PROCS'           to set the number of MPI processes used in demo codes.")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display options
message(STATUS "Build driver codes:        ${MCNLA_BUILD_DRIVER}")
message(STATUS "Build demo codes:          ${MCNLA_BUILD_DEMO}")
message(STATUS "Build test codes:          ${MCNLA_BUILD_TEST}")
message(STATUS "Build documentation:       ${MCNLA_BUILD_DOC}")

message(STATUS "")

message(STATUS "Use OpenMP:                ${OpenMP_CXX_FLAGS}")

if(MCNLA_BUILD_BIN)
  message(STATUS "Use MPI:                   ${MPI_LIBRARIES}")
else()
  message(STATUS "Use MPI:                   OFF")
endif()

if(MCNLA_BUILD_BIN)
  if(NOT MCNLA_USE_MKL)
    set(LAPACK_LIBS ${LAPACK_LIBRARIES})
    list(REMOVE_DUPLICATES LAPACK_LIBS)
    message(STATUS "Use BLAS:                  ${LAPACK_LIBS}")
  else()
    message(STATUS "Use BLAS: (Intel MKL)      ${MKL_LIBS}")
    if(MKL_OMP)
      message(STATUS "Use multithread MKL:       ${MKL_OMP_LIBRARY}")
    else()
      message(STATUS "Use multithread MKL:       OFF")
    endif()
  endif()
endif()

# if(MCNLA_BUILD_BIN AND MCNLA_USE_GPU)
#   message(STATUS "Use GPU:                   ${CUDA_TOOLKIT_ROOT_DIR}")
#   message(STATUS "Use MAGMA:                 ${MAGMA_LIBRARIES}")
# else()
#   message(STATUS "Use GPU:                   OFF")
# endif()

if(MCNLA_BUILD_TEST)
  message(STATUS "Use Google Test:           ${GTEST_BOTH_LIBRARIES}")
else()
  message(STATUS "Use Google Test:           OFF")
endif()

if(MCNLA_BUILD_DOC)
  message(STATUS "Use Doxygen:               ${DOXYGEN_EXECUTABLE}")
else()
  message(STATUS "Use Doxygen:               OFF")
endif()

message(STATUS "")

if(NOT MCNLA_USE_ILP64)
  message(STATUS "System integer size:       32bit (LP64)")
else()
  message(STATUS "System integer size:       64bit (ILP64)")
endif()

if(MCNLA_BUILD_BIN)
  message(STATUS "MPI processes (demo only): ${MPI_PROCS}")
endif()

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
