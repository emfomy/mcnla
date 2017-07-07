#pragma once

#include "test.hpp"

template <typename _Val>
using DenseVectorDeathTest = DenseVectorTest<_Val>;
TYPED_TEST_CASE(DenseVectorDeathTest, MyTypes);

template <typename _Val>
using DenseVectorDeathTest_Size8_Stride1 = DenseVectorTest_Size8_Stride1<_Val>;
TYPED_TEST_CASE(DenseVectorDeathTest_Size8_Stride1, MyTypes);

template <typename _Val>
using DenseVectorDeathTest_Size8_Stride3 = DenseVectorTest_Size8_Stride3<_Val>;
TYPED_TEST_CASE(DenseVectorDeathTest_Size8_Stride3, MyTypes);
