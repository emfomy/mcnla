#pragma once

#include <gtest/gtest.h>
#include <mcnla.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Scalar, mcnla::index_t _length, mcnla::index_t _stride, mcnla::index_t _memsize, mcnla::index_t _offset>
class DenseVectorTestBase : public testing::Test {

 protected:

  const mcnla::index_t length_   = _length;
  const mcnla::index_t stride_   = _stride;
  const mcnla::index_t memsize_  = _memsize;
  const mcnla::index_t capacity_ = _memsize-_offset;
  const mcnla::index_t offset_   = _offset;

  std::valarray<_Scalar> valarray_;
  mcnla::matrix::DenseVector<_Scalar> vec_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    mcnla::matrix::Array<_Scalar> array(memsize_, offset_);
    vec_ = mcnla::matrix::DenseVector<_Scalar>(length_, stride_, array);
    mcnla::lapack::larnv<3>(vec_, iseed);
    valarray_ = vec_.getValueValarray();
  }

  virtual void TearDown() {}

};


template <typename _Scalar>
class DenseVectorTest : public testing::Test {};
TYPED_TEST_CASE(DenseVectorTest, MyTypes);

template <typename _Scalar>
class DenseVectorTest_Size8_Stride1 : public DenseVectorTestBase<_Scalar, 8, 1, 10, 2> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride1, MyTypes);

template <typename _Scalar>
class DenseVectorTest_Size8_Stride3 : public DenseVectorTestBase<_Scalar, 8, 3, 25, 3> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride3, MyTypes);
