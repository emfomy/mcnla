#pragma once

#include <gtest/gtest.h>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Val, mcnla::Trans _trans,
          mcnla::index_t _nrow, mcnla::index_t _ncol, mcnla::index_t _pitch, mcnla::index_t _memsize, mcnla::index_t _offset>
class DenseMatrixTestBase : public testing::Test {

 protected:

  const mcnla::index_t nrow_     = _nrow;
  const mcnla::index_t ncol_     = _ncol;
  const mcnla::index_t pitch_    = _pitch;
  const mcnla::index_t memsize_  = _memsize;
  const mcnla::index_t capacity_ = _memsize-_offset;
  const mcnla::index_t offset_   = _offset;

  const _Val *valptr0_;
  mcnla::matrix::DenseMatrix<_Val, _trans> mat_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    mcnla::matrix::Array<_Val> array(memsize_, offset_);
    mat_.reconstruct(nrow_, ncol_, pitch_, array);
    mcnla::la::larnv<3>(mat_.unfold(), iseed);
    valptr0_ = array.get();
  }

  virtual void TearDown() {}

};


template <typename _Val>
class DenseMatrixTest_ColMajor : public testing::Test {};
TYPED_TEST_CASE(DenseMatrixTest_ColMajor, MyTypes);

template <typename _Val>
class DenseMatrixTest_RowMajor : public testing::Test {};
TYPED_TEST_CASE(DenseMatrixTest_RowMajor, MyTypes);

template <typename _Val>
class DenseMatrixTest_ColMajor_Size8x5_Pitch8
  : public DenseMatrixTestBase<_Val, mcnla::Trans::NORMAL, 8, 5, 8,  80,  40> {};
TYPED_TEST_CASE(DenseMatrixTest_ColMajor_Size8x5_Pitch8, MyTypes);

template <typename _Val>
class DenseMatrixTest_ColMajor_Size8x5_Pitch10
  : public DenseMatrixTestBase<_Val, mcnla::Trans::NORMAL, 8, 5, 10, 100, 52> {};
TYPED_TEST_CASE(DenseMatrixTest_ColMajor_Size8x5_Pitch10, MyTypes);

template <typename _Val>
class DenseMatrixTest_RowMajor_Size8x5_Pitch5
  : public DenseMatrixTestBase<_Val, mcnla::Trans::TRANS, 8, 5, 5,  50,  10> {};
TYPED_TEST_CASE(DenseMatrixTest_RowMajor_Size8x5_Pitch5, MyTypes);

template <typename _Val>
class DenseMatrixTest_RowMajor_Size8x5_Pitch10
  : public DenseMatrixTestBase<_Val, mcnla::Trans::TRANS, 8, 5, 10, 100, 25> {};
TYPED_TEST_CASE(DenseMatrixTest_RowMajor_Size8x5_Pitch10, MyTypes);
