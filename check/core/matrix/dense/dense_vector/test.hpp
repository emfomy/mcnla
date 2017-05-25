#pragma once

#include <gtest/gtest.h>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Val, mcnla::index_t _len, mcnla::index_t _stride, mcnla::index_t _memsize, mcnla::index_t _offset>
class DenseVectorTestBase : public testing::Test {

 protected:

  const mcnla::index_t len_      = _len;
  const mcnla::index_t stride_   = _stride;
  const mcnla::index_t memsize_  = _memsize;
  const mcnla::index_t capacity_ = _memsize-_offset;
  const mcnla::index_t offset_   = _offset;

  const _Val *valptr0_;
  mcnla::matrix::DenseVector<_Val> vec_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    mcnla::matrix::Array<_Val> array(memsize_, offset_);
    vec_.reconstruct(len_, stride_, array);
    mcnla::la::larnv<3>(vec_, iseed);
    valptr0_ = array.get();
  }

  virtual void TearDown() {}

};


template <typename _Val>
class DenseVectorTest : public testing::Test {};
TYPED_TEST_CASE(DenseVectorTest, MyTypes);

template <typename _Val>
class DenseVectorTest_Size8_Stride1 : public DenseVectorTestBase<_Val, 8, 1, 10, 2> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride1, MyTypes);

template <typename _Val>
class DenseVectorTest_Size8_Stride3 : public DenseVectorTestBase<_Val, 8, 3, 25, 3> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride3, MyTypes);
