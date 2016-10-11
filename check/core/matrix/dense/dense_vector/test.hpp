#include <gtest/gtest.h>
#include <mcnla.hpp>

template <typename _Scalar>
class DenseVectorTest : public testing::Test {

 protected:

  const mcnla::index_t length_;
  const mcnla::index_t stride_;
  const mcnla::index_t capacity_;

  std::valarray<_Scalar> valarray_;
  mcnla::matrix::DenseVector<_Scalar> vec_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  DenseVectorTest(
      const mcnla::index_t length,
      const mcnla::index_t stride,
      const mcnla::index_t capacity
  ) : length_(length),
      stride_(stride),
      capacity_(capacity) {}

  virtual void SetUp() {
    vec_ = mcnla::matrix::DenseVector<_Scalar>(length_, stride_, capacity_);
    mcnla::lapack::larnv<3>(vec_, iseed);
    valarray_ = vec_.getValueValarray();
  }

  virtual void TearDown() {}

};

template <typename _Scalar>
class DenseVectorTest_Length8_Stride1 : public DenseVectorTest<_Scalar> {

 protected:

  DenseVectorTest_Length8_Stride1() : DenseVectorTest<_Scalar>(8, 1, 10) {}

};

template <typename _Scalar>
class DenseVectorTest_Length8_Stride3 : public DenseVectorTest<_Scalar> {

 protected:

  DenseVectorTest_Length8_Stride3() : DenseVectorTest<_Scalar>(8, 3, 30) {}

};

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;
TYPED_TEST_CASE(DenseVectorTest_Length8_Stride1, MyTypes);
TYPED_TEST_CASE(DenseVectorTest_Length8_Stride3, MyTypes);
