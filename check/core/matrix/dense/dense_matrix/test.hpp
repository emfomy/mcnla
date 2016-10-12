#pragma once

#include <gtest/gtest.h>
#include <mcnla.hpp>

using MyTypes = testing::Types<float, double, std::complex<float>, std::complex<double>>;

template <typename _Scalar, mcnla::Layout _layout,
          mcnla::index_t _nrow, mcnla::index_t _ncol, mcnla::index_t _pitch, mcnla::index_t _capacity>
class DenseMatrixTest : public testing::Test {

 protected:

  const mcnla::index_t nrow_     = _nrow;
  const mcnla::index_t ncol_     = _ncol;
  const mcnla::index_t pitch_    = _pitch;
  const mcnla::index_t capacity_ = _capacity;

  std::valarray<_Scalar> valarray_;
  mcnla::matrix::DenseMatrix<_Scalar, _layout> mat_;

  mcnla::index_t iseed[4] = {0, 0, 0, 1};

  virtual void SetUp() {
    mat_ = mcnla::matrix::DenseMatrix<_Scalar, _layout>(nrow_, ncol_, pitch_, capacity_);
    mcnla::lapack::larnv<3>(mat_.vectorize(), iseed);
    valarray_ = mat_.getValueValarray();
  }

  virtual void TearDown() {}

};

template <typename _Scalar>
class DenseMatrixTest_ColMajor_Size8x5_Pitch8 : public DenseMatrixTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 8, 100> {};
TYPED_TEST_CASE(DenseMatrixTest_ColMajor_Size8x5_Pitch8, MyTypes);

template <typename _Scalar>
class DenseMatrixTest_ColMajor_Size8x5_Pitch10 : public DenseMatrixTest<_Scalar, mcnla::Layout::COLMAJOR, 8, 5, 10, 100> {};
TYPED_TEST_CASE(DenseMatrixTest_ColMajor_Size8x5_Pitch10, MyTypes);

template <typename _Scalar>
class DenseMatrixTest_RowMajor_Size8x5_Pitch5 : public DenseMatrixTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 5, 100> {};
TYPED_TEST_CASE(DenseMatrixTest_RowMajor_Size8x5_Pitch5, MyTypes);

template <typename _Scalar>
class DenseMatrixTest_RowMajor_Size8x5_Pitch10 : public DenseMatrixTest<_Scalar, mcnla::Layout::ROWMAJOR, 8, 5, 10, 100> {};
TYPED_TEST_CASE(DenseMatrixTest_RowMajor_Size8x5_Pitch10, MyTypes);
