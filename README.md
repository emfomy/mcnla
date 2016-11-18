# MCNLA
Monte Carlo Numerical Linear Algebra Package

### Git
* https://github.com/wlab-pro/mcnla

### Documentation
* http://wlab-pro.github.io/mcnla

### Author
* Mu Yang <<emfomy@gmail.com>>

### Package Requirement
* CMake 2.8+.
* C++ compiler with C++11 support (GCC 5+ recommended).
* LAPACK library.
* MPI Library.

#### Optional
* [Intel&reg; Math Kernel Library](https://software.intel.com/en-us/intel-mkl) (Used for LAPACK and BLAS).
* [DOxygen](http://www.stack.nl/~dimitri/doxygen/) (Used for documentation).
* [Google Test Library](https://github.com/google/googletest) (Used for code testing).

### Installation

Please use the following commands to create Makefiles

```
mkdir build
cd build
cmake <path-to-source>
```

To change options or error occurs, use

```
ccmake <path-to-source>
```

#### Settings

* Set `MCNLA_BUILD_DEMO` to build demo codes.
* Set `MCNLA_BUILD_DOC` to build documentation.
* Set `MCNLA_BUILD_TEST` to build test codes.

* Set `MCNLA_USE_ILP64` to change the system integer size. (`OFF`: 32bit / `ON`: 64bit)
* Set `MCNLA_USE_MKL` to enable Intel MKL.
* Set `MPI_PROCS` to set the number of MPI processes. (Default: 4)

* Set `MKL_ROOT` for the root path of Intel MKL. (Automatically set if environment variable `MKLROOT` is set.)
* Set `GTEST_ROOT` for the root path of Google Test.

#### Makefile

| Command      | Detail                   |
|--------------|--------------------------|
| `make demo`  | build demo code          |
| `make run`   | run demo code            |
| `make doc`   | build documentation      |
| `make check` | build and run test codes |
| `make help`  | display make-rules       |

#### Know Issue
* MCNLA is not compatible with Intel MPI on single node system.

### Reference
* [Ting-Li Chen, Dawei D. Chang, Su-Yun Huang, Hung Chen, Chienyao Lin, Weichung Wang, “Integrating Multiple Random Sketches for Singular Value Decomposition”](https://arxiv.org/abs/1608.08285)
