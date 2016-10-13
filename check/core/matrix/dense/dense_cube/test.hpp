#pragma once

#include <gtest/gtest.h>
#include <mcnla.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Scalar, mcnla::Layout _layout, mcnla::index_t _nrow, mcnla::index_t _ncol, mcnla::index_t _npage,
          mcnla::index_t _pitch0, mcnla::index_t _pitch1, mcnla::index_t _memsize, mcnla::index_t _offset>
class DenseCubeTest : public testing::Test {

 protected:

  const mcnla::index_t nrow_     = _nrow;
  const mcnla::index_t ncol_     = _ncol;
  const mcnla::index_t npage_    = _npage;
  const mcnla::index_t pitch0_   = _pitch0;
  const mcnla::index_t pitch1_   = _pitch1;
  const mcnla::index_t memsize_  = _memsize;
  const mcnla::index_t capacity_ = _memsize-_offset;
  const mcnla::index_t offset_   = _offset;

  std::valarray<_Scalar> valarray_;
  mcnla::matrix::DenseCube<_Scalar, _layout> cube_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    mcnla::matrix::Array<_Scalar> array(memsize_, offset_);
    cube_ = mcnla::matrix::DenseCube<_Scalar, _layout>(nrow_, ncol_, npage_, pitch0_, pitch1_, array);
    mcnla::lapack::larnv<3>(cube_.vectorize(), iseed);
    valarray_ = cube_.getValueValarray();
  }

  virtual void TearDown() {}

};

template <typename _Scalar>
class DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5
  : public DenseCubeTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 7, 8,   5,  400, 120> {};
TYPED_TEST_CASE(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5,   MyTypes);

template <typename _Scalar>
class DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10
  : public DenseCubeTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 7, 8,  10,  800, 280> {};
TYPED_TEST_CASE(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10,  MyTypes);

template <typename _Scalar>
class DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5
  : public DenseCubeTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 7, 10,  5,  500, 152> {};
TYPED_TEST_CASE(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5,  MyTypes);

template <typename _Scalar>
class DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10
  : public DenseCubeTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 7, 10, 10, 1000, 352> {};
TYPED_TEST_CASE(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, MyTypes);

template <typename _Scalar>
class DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8
  : public DenseCubeTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 7,  5,  8,  400, 120> {};
TYPED_TEST_CASE(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8,   MyTypes);

template <typename _Scalar>
class DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10
  : public DenseCubeTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 7, 5,  10,  500, 160> {};
TYPED_TEST_CASE(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10,  MyTypes);

template <typename _Scalar>
class DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8
  : public DenseCubeTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 7, 10,  8,  800, 245> {};
TYPED_TEST_CASE(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8,  MyTypes);

template <typename _Scalar>
class DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10
  : public DenseCubeTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 7, 10, 10, 1000, 325> {};
TYPED_TEST_CASE(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, MyTypes);
