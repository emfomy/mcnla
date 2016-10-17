#pragma once

#include "test.hpp"

template <typename _Scalar>
using DenseMatrixDeathTest_ColMajor = DenseMatrixTest_ColMajor<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_ColMajor, MyTypes);

template <typename _Scalar>
using DenseMatrixDeathTest_RowMajor = DenseMatrixTest_RowMajor<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_RowMajor, MyTypes);

template <typename _Scalar>
using DenseMatrixDeathTest_ColMajor_Size8x5_Pitch8  = DenseMatrixTest_ColMajor_Size8x5_Pitch8<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_ColMajor_Size8x5_Pitch8, MyTypes);

template <typename _Scalar>
using DenseMatrixDeathTest_ColMajor_Size8x5_Pitch10 = DenseMatrixTest_ColMajor_Size8x5_Pitch10<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_ColMajor_Size8x5_Pitch10, MyTypes);

template <typename _Scalar>
using DenseMatrixDeathTest_RowMajor_Size8x5_Pitch5  = DenseMatrixTest_RowMajor_Size8x5_Pitch5<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_RowMajor_Size8x5_Pitch5, MyTypes);

template <typename _Scalar>
using DenseMatrixDeathTest_RowMajor_Size8x5_Pitch10  = DenseMatrixTest_RowMajor_Size8x5_Pitch10<_Scalar>;
TYPED_TEST_CASE(DenseMatrixDeathTest_RowMajor_Size8x5_Pitch10, MyTypes);
