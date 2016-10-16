#pragma once

#include "test.hpp"

template <typename _Scalar>
class DenseVectorDeathTest : public testing::Test {};
TYPED_TEST_CASE(DenseVectorDeathTest, MyTypes);

template <typename _Scalar>
using DenseVectorDeathTest_Size8_Stride1 = DenseVectorTest_Size8_Stride1<_Scalar>;
TYPED_TEST_CASE(DenseVectorDeathTest_Size8_Stride1, MyTypes);

template <typename _Scalar>
using DenseVectorDeathTest_Size8_Stride3 = DenseVectorTest_Size8_Stride3<_Scalar>;
TYPED_TEST_CASE(DenseVectorDeathTest_Size8_Stride3, MyTypes);
