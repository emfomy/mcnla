#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor, Check) {
}


TYPED_TEST(DenseMatrixTest_RowMajor, Check) {
}

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(mat.nrow(),  nrow);
  EXPECT_EQ(mat.ncol(),  ncol);
  EXPECT_EQ(mat.nelem(), nrow * ncol);
  EXPECT_EQ(mat.pitch(), pitch);

  EXPECT_EQ(mat.sizes(), std::make_tuple(nrow, ncol));

  EXPECT_TRUE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.capacity(), capacity);
  EXPECT_EQ(mat.offset(),   offset);

  EXPECT_EQ(mat.nrow(),     mat.pitch());
  EXPECT_EQ(mat.capacity(), nrow * ncol);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valptr0[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valptr0[offset + i + j*pitch]);
    }
  }
  for ( auto value : mat ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : mat ) {
    EXPECT_NE(value, TypeParam(0));
  }
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(mat.nrow(),  nrow);
  EXPECT_EQ(mat.ncol(),  ncol);
  EXPECT_EQ(mat.nelem(), nrow * ncol);
  EXPECT_EQ(mat.pitch(), pitch);

  EXPECT_EQ(mat.sizes(), std::make_tuple(nrow, ncol));

  EXPECT_FALSE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.capacity(), capacity);
  EXPECT_EQ(mat.offset(),   offset);

  EXPECT_LT(mat.nrow(),     mat.pitch());
  EXPECT_EQ(mat.capacity(), pitch * ncol - (pitch-nrow));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valptr0[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valptr0[offset + i + j*pitch]);
    }
  }
  for ( auto value : mat ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : mat ) {
    EXPECT_NE(value, TypeParam(0));
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(mat.nrow(),  nrow);
  EXPECT_EQ(mat.ncol(),  ncol);
  EXPECT_EQ(mat.nelem(), nrow * ncol);
  EXPECT_EQ(mat.pitch(), pitch);

  EXPECT_EQ(mat.sizes(), std::make_tuple(nrow, ncol));

  EXPECT_TRUE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.capacity(), capacity);
  EXPECT_EQ(mat.offset(),   offset);

  EXPECT_EQ(mat.ncol(),     mat.pitch());
  EXPECT_EQ(mat.capacity(), nrow * ncol);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valptr0[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valptr0[offset + i*pitch + j]);
    }
  }
  for ( auto value : mat ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : mat ) {
    EXPECT_NE(value, TypeParam(0));
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(mat.nrow(),  nrow);
  EXPECT_EQ(mat.ncol(),  ncol);
  EXPECT_EQ(mat.nelem(), nrow * ncol);
  EXPECT_EQ(mat.pitch(), pitch);

  EXPECT_EQ(mat.sizes(), std::make_tuple(nrow, ncol));

  EXPECT_FALSE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.capacity(), capacity);
  EXPECT_EQ(mat.offset(),   offset);

  EXPECT_LT(mat.ncol(),     mat.pitch());
  EXPECT_EQ(mat.capacity(), nrow * pitch - (pitch-ncol));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valptr0[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valptr0[offset + i*pitch + j]);
    }
  }
  for ( auto value : mat ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : mat ) {
    EXPECT_NE(value, TypeParam(0));
  }
}
