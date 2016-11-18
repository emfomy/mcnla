# MCNLA
Monte Carlo Numerical Linear Algebra Package

### Git
* https://github.com/wlab-pro/mcnla

### Documentation
* http://wlab-pro.github.io/mcnla

### Author
* Mu Yang <<emfomy@gmail.com>>

### Package Requirement
* CMake 3+.
* C++ compiler with C++11 support (GCC 5+ recommended).
* LAPACK library.
* MPI Library.

#### Optional
* [Intel&reg; Math Kernel Library](https://software.intel.com/en-us/intel-mkl) (**Recommended** for better performance, used for LAPACK and BLAS).
* [DOxygen](http://www.stack.nl/~dimitri/doxygen/) (Used for documentation).
* [Google Test Library](https://github.com/google/googletest) (Used for code testing).

### Installation

Please use the following commands to create Makefiles

```
mkdir build
cd build
cmake ..
```

#### Options

Use the following commands to options

```
ccmake ..
```

* Set `MCNLA_BUILD_DEMO` to build demo codes.
* Set `MCNLA_BUILD_TEST` to build test codes.
* Set `MCNLA_BUILD_DOC`  to build documentation.

* Set `MCNLA_USE_ILP64` to change the system integer size. (`OFF`: 32bit / `ON`: 64bit)
* Set `MCNLA_USE_MKL`   to enable Intel MKL.
* Set `MPI_PROCS`       to set the number of MPI processes. (Default: 4)

* Set `MKL_ROOT`   for the root path of Intel MKL. (Automatically set if environment variable `MKLROOT` is set.)
* Set `GTEST_ROOT` for the root path of Google Test.

#### Makefile

| Command      | Detail                   |
|--------------|--------------------------|
| `make demo`  | build demo code          |
| `make run`   | run demo code            |
| `make check` | build and run test codes |
| `make doc`   | build documentation      |
| `make help`  | display make-rules       |

### Q&amp;A

#### How to set CMake options?

* Use `ccmake ..` or `ccmake <path-to-source>` in the `build` folder.
* Press <Enter> on the option you want to change, change it, and press `<Enter>` again.
* After changing the options, press `<c>` to configure, and press `<g>` to generate Makefiles if configured successfully.
* To quit without saving, press `<q>`.

#### Why Intel MKL is not found?

* Source `mklvars.sh` in the `bin` folder of your Intel MKL to set the environment variables.

#### Why Google Test is not found?

* `GTEST_ROOT` should be set to a folder containing `include` and `lib` of Google Test.
* Make sure you set `GTEST_ROOT` with `ccmake`.

#### How to use 64bit integer?

* Set `MCNLA_USE_ILP64` with `ccmake`.
* If you want to compile directly, add `-DMCNLA_USE_ILP64` to compiler flag.
* Make sure your LAPACK&amp;BLAS / Intel MKL uses 64bit integer. Make sure you uses the correct library and flags of Intel MKl.

### Reference
* [Ting-Li Chen, Dawei D. Chang, Su-Yun Huang, Hung Chen, Chienyao Lin, Weichung Wang, “Integrating Multiple Random Sketches for Singular Value Decomposition”](https://arxiv.org/abs/1608.08285)
