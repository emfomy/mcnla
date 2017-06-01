if(MCNLA_BUILD_BIN)
  # Set default variables
  set(INCS "")
  set(LIBS "")
  set(COMFLGS "")
  set(LNKFLGS "")

  # Set complier flags
  set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -g -Wall -Wextra -pedantic")
  # set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -g -fsanitize=address -Wall -Wextra -pedantic")

  # MPI
  find_package(MPI REQUIRED)
  if(MPI_FOUND)
    list(APPEND INCS "${MPI_INCLUDE_PATH}")
    list(APPEND LIBS "${MPI_LIBRARIES}")
    set(COMFLGS "${COMFLGS} ${MPI_COMPILE_FLAGS}")
    set(LNKFLGS "${LNKFLGS} ${MPI_LINK_FLAGS}")
  endif()

  # MKL
  if(MCNLA_USE_MKL)
    find_package(MKL REQUIRED)
    if(MKL_FOUND)
      list(APPEND INCS "${MKL_INCLUDES}")
      list(APPEND LIBS "${MKL_LIBRARIES}")
      set(COMFLGS "${COMFLGS} ${MKL_FLAGS}")
    endif()
  endif()

  # LAPACK
  if(NOT MCNLA_USE_MKL)
    find_package(LAPACK REQUIRED)
    if(LAPACK_FOUND)
      list(APPEND LIBS "${LAPACK_LIBRARIES}")
    endif()
  endif()

  # OpenMP
  if(MCNLA_OMP)
    set(OpenMP ${MCNLA_OMP})

    find_package(OpenMP REQUIRED)
    if(OpenMP_FOUND)
      set(COMFLGS "${COMFLGS} ${OpenMP_CXX_FLAGS}")
      set(LNKFLGS "${LNKFLGS} ${OpenMP_CXX_FLAGS}")
    endif()

    find_package(OpenMPLib REQUIRED)
    if(OpenMPLib_FOUND)
      list(APPEND LIBS "${OpenMP_LIBRARIES}")
    endif()

    unset(OpenMP)
  endif()
endif()

# CUDA & MAGMA
# if(MCNLA_USE_GPU)
#   find_package(CUDA REQUIRED)
#   find_package(MAGMA REQUIRED)
#   if(MAGMA_FOUND)
#     list(APPEND INCS "${MAGMA_INCLUDES}")
#     list(APPEND LIBS "${MAGMA_LIBRARIES}" "${CUDA_CUDART_LIBRARY}" "${CUDA_cublas_LIBRARY}" "${CUDA_cusparse_LIBRARY}")
#   endif()
# endif()

# GTest
if(MCNLA_BUILD_TEST)
  find_package(GTest 1.8 REQUIRED)
endif()

# DOxygen
if(MCNLA_BUILD_DOC)
  find_package(Doxygen REQUIRED)
endif()
