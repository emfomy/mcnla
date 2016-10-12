#pragma once

#include <gtest/gtest.h>
#include <mcnla.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Scalar, mcnla::index_t _length, mcnla::index_t _stride, mcnla::index_t _capacity>
class DenseVectorTest : public testing::Test {

 protected:

  const mcnla::index_t length_   = _length;
  const mcnla::index_t stride_   = _stride;
  const mcnla::index_t capacity_ = _capacity;

  std::valarray<_Scalar> valarray_;
  mcnla::matrix::DenseVector<_Scalar> vec_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    vec_ = mcnla::matrix::DenseVector<_Scalar>(length_, stride_, capacity_);
    mcnla::lapack::larnv<3>(vec_, iseed);
    valarray_ = vec_.getValueValarray();
  }

  virtual void TearDown() {}

};

template <typename _Scalar>
class DenseVectorTest_Size8_Stride1 : public DenseVectorTest<_Scalar, 8, 1, 10> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride1, MyTypes);

template <typename _Scalar>
class DenseVectorTest_Size8_Stride3 : public DenseVectorTest<_Scalar, 8, 3, 30> {};
TYPED_TEST_CASE(DenseVectorTest_Size8_Stride3, MyTypes);
