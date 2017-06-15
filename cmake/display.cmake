# Display message
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
message(STATUS "Set 'MCNLA_BLAS'           to select BLAS/LAPACK library. [BLAS/MKL]")
message(STATUS "Set 'MCNLA_BUILD_DEMO'     to build demo codes.")
message(STATUS "Set 'MCNLA_BUILD_DOC'      to build documentation.")
message(STATUS "Set 'MCNLA_BUILD_DRIVER'   to build driver codes.")
message(STATUS "Set 'MCNLA_BUILD_REPORT'   to build report codes.")
message(STATUS "Set 'MCNLA_BUILD_TEST'     to build test codes.")
message(STATUS "Set 'MCNLA_INSTALL_DEMO'   to install demos.")
# message(STATUS "Set 'MCNLA_USE_GPU'        to enable GPU support.")
message(STATUS "Set 'MCNLA_INT_SIZE'       to select system integer size. [32/64]")
message(STATUS "Set 'MCNLA_OMP'            to select OpenMP library. [OFF/GOMP/IOMP] (Require 'MCNLA_BLAS = MKL')")
message(STATUS "")
message(STATUS "Set 'GTEST_ROOT'           for the root path of Google Test.         (Require 'MCNLA_BUILD_TEST')")
message(STATUS "Set 'INTEL_ROOT'           for the root path of Intel libraries.     (Require 'MCNLA_BLAS = MKL')")
message(STATUS "Set 'MKL_ROOT'             for the root path of Intel MKL.           (Require 'MCNLA_BLAS = MKL')")
message(STATUS "Set 'MPI_PROCS'            to set the number of MPI processes used in demo codes.")
message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")

# Display options
message(STATUS "Build driver codes:        ${MCNLA_BUILD_DRIVER}")
message(STATUS "Build demo codes:          ${MCNLA_BUILD_DEMO}")
message(STATUS "Build test codes:          ${MCNLA_BUILD_TEST}")
message(STATUS "Build documentation:       ${MCNLA_BUILD_DOC}")

message(STATUS "")

# Display libraries
if(MCNLA_OMP)
  message(STATUS "Use OpenMP:                ${OpenMP_CXX_FLAGS} ${OpenMP_LIBRARIES}")
else()
  message(STATUS "Use OpenMP:                OFF")
endif()

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

# Display flags
set(incs "-I<MCNLA-install-path>/include")
foreach(i ${INCS})
  string(REGEX REPLACE "^ " "" i "${i}")
  set(incs "${incs} -isystem ${i}")
endforeach()
string(REGEX REPLACE "  +" " " incs "${incs}")
string(REGEX REPLACE "^ " "" incs "${incs}")

set(libs "")
foreach(l ${LIBS})
  string(REGEX REPLACE "^ " "" l "${l}")
  string(SUBSTRING ${l} 0 1 l0)
  if(${l0} MATCHES "-")
    set(libs "${libs} ${l}")
  else()
    set(libs "${libs} -l${l}")
  endif()
endforeach()
string(REGEX REPLACE "  +" " " libs "${libs}")
string(REGEX REPLACE "^ " "" libs "${libs}")

set(defs "")
foreach(d ${DEFS})
  string(REGEX REPLACE "^ " "" d "${d}")
  string(SUBSTRING ${d} 0 1 d0)
  if(${d0} MATCHES "-")
    set(defs "${defs} ${d}")
  else()
    set(defs "${defs} -D${d}")
  endif()
endforeach()
string(REGEX REPLACE "  +" " " comflgs "${CMAKE_CXX_FLAGS} -DNDEBUG ${COMFLGS} ${defs}")
string(REGEX REPLACE "^ " "" comflgs "${comflgs}")

string(REGEX REPLACE "  +" " " lnkflgs "${CMAKE_CXX_FLAGS} ${LNKFLGS}")
string(REGEX REPLACE "^ " "" lnkflgs "${lnkflgs}")

message(STATUS "Compiler:                  ${CMAKE_CXX_COMPILER}")
message(STATUS "Compile flags:             ${comflgs}")
message(STATUS "Link flags:                ${lnkflgs}")
message(STATUS "Include pathes:            ${incs}")
message(STATUS "Libraries:                 ${libs}")

message(STATUS "")
message(STATUS "================================================================================")
message(STATUS "")
