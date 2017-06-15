# MCNLA
Monte Carlo Numerical Linear Algebra Package

## Information

### Git
* https://github.com/wlab-pro/mcnla

### Documentation
* http://wlab-pro.github.io/mcnla

### Author
* Mu Yang <<emfomy@gmail.com>>

### Tutorial
* @ref tutorial_main

## Requirements
* [CMake](https://cmake.org) 2.8+ (CMake 3+ recommended).
* C++ compiler with C++11 support ([GCC](https://gcc.gnu.org) 5+ recommended).
* [BLAS](http://www.netlib.org/blas) & [LAPACK](http://www.netlib.org/lapack) library.
* [OpenMP](http://openmp.org) Library.
* MPI Library ([MPICH](http://www.mpich.org) or [OpenMPI](https://www.open-mpi.org)).

### Optional
* [Intel&reg; Math Kernel Library](https://software.intel.com/en-us/intel-mkl) (**Recommended** for better performance, used for BLAS & LAPACK).
<!-- * [MAGMA](http://icl.cs.utk.edu/magma/) 2+ (Used for BLAS & LAPACK with GPU support). -->
* [DOxygen](http://www.stack.nl/~dimitri/doxygen/) (Used for documentation).
* [Google Test Library](https://github.com/google/googletest) (Used for code testing).

## Installation

Please use the following commands to create Makefiles

```
mkdir build
cd build
cmake <path-to-source>
```

### Options

Use the following command to set options

```
ccmake <path-to-source>
```

* Set 'MCNLA_BLAS'          to select BLAS/LAPACK library. \[BLAS/MKL\]
* Set 'MCNLA_BUILD_DEMO'    to build demo codes.
* Set 'MCNLA_BUILD_DOC'     to build documentation.
* Set 'MCNLA_BUILD_DRIVER'  to build driver codes.
* Set 'MCNLA_BUILD_REPORT'  to build report codes.
* Set 'MCNLA_BUILD_TEST'    to build test codes.
* Set 'MCNLA_INSTALL_DEMO'  to install demos.
<!-- * Set `MCNLA_USE_GPU`       to enable GPU support. -->
* Set 'MCNLA_INT_SIZE'      to select system integer size. \[32/64\]
* Set 'MCNLA_OMP'           to select OpenMP library. \[OFF/GOMP/IOMP\] (Require 'MCNLA_BLAS = MKL')

* Set 'GTEST_ROOT'          for the root path of Google Test.           (Require 'MCNLA_BUILD_TEST')
* Set 'INTEL_ROOT'          for the root path of Intel libraries.       (Require 'MCNLA_BLAS = MKL')
* Set 'MKL_ROOT'            for the root path of Intel MKL.             (Require 'MCNLA_BLAS = MKL')
* Set 'MPI_PROCS'           to set the number of MPI processes used in demo codes.

### Makefile

| Command        | Detail                   |
|----------------|--------------------------|
| `make all`     | build all binaries       |
| `make install` | install package          |
| `make run`     | run demo code            |
| `make check`   | build and run test codes |
| `make doc`     | build documentation      |
| `make help`    | display make-rules       |

### Definitions

* Define `MCNLA_USE_ILP64`        to use 64-bit integer.
* Define `MCNLA_USE_MKL`          to enable Intel MKL.
<!-- * Define `MCNLA_USE_GPU`          to enable GPU support. -->
* Define `MCNLA_DISABLE_LITERAL`  to disable literal definition in global namespace.

## Q&amp;A

### How to set CMake options?

* Use `ccmake ..` or `ccmake <path-to-source>` in the `build` folder.
* Press `<Enter>` on the option you want to change, change it, and press `<Enter>` again.
* After changing the options, press `<c>` to configure, and press `<g>` to generate Makefiles if configured successfully.
* To quit without saving, press `<q>`.

### Why Intel MKL is not found?

* Source `mklvars.sh` in the `bin` folder of your Intel MKL to set the environment variables.

### Why Google Test is not found?

* Set `GTEST_ROOT` to a folder containing `include` and `lib` of Google Test.

### How to use 64-bit integer?

* Set `MCNLA_USE_ILP64` with `ccmake`.
* If you want to compile directly, add `-DMCNLA_USE_ILP64` to compiler flag.
* Make sure your LAPACK&amp;BLAS / Intel MKL uses 64bit integer. Make sure you uses the correct library and flags of Intel MKL.

### `std::bad_alloc` occurs. What should I do?

* Possible issues:
  - Not enough memory. You might request a vector/matrix which size exceed your memory size.
  - Index overflow. Use 64-bit integer instead of 32-bit integer. For example, if you request a `1e5` x `1e5` matrix, there will be `1e10` elements, which is larger than the maximum number in 32-bit integer (about `2.1e9`). Using 64-bit integer may solve this problem.

## Reference
* [Ting-Li Chen, Dawei D. Chang, Su-Yun Huang, Hung Chen, Chienyao Lin, Weichung Wang, “Integrating Multiple Random Sketches for Singular Value Decomposition”](https://arxiv.org/abs/1608.08285)

## License
@include LICENSE.md
