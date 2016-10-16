#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(mat.getNrow(),  nrow);
  EXPECT_EQ(mat.getNcol(),  ncol);
  EXPECT_EQ(mat.getNelem(), nrow * ncol);
  EXPECT_EQ(mat.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(mat.getPitch(), pitch);

  EXPECT_TRUE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.getCapacity(), capacity);
  EXPECT_EQ(mat.getOffset(),   offset);

  EXPECT_EQ(mat.getNrow(), mat.getPitch());
  EXPECT_EQ(mat.getCapacity(), nrow * ncol);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valarray[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch]);
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
  const auto valarray = this->valarray_;

  EXPECT_EQ(mat.getNrow(),  nrow);
  EXPECT_EQ(mat.getNcol(),  ncol);
  EXPECT_EQ(mat.getNelem(), nrow * ncol);
  EXPECT_EQ(mat.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(mat.getPitch(), pitch);

  EXPECT_FALSE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.getCapacity(), capacity);
  EXPECT_EQ(mat.getOffset(),   offset);

  EXPECT_LT(mat.getNrow(), mat.getPitch());
  EXPECT_EQ(mat.getCapacity(), pitch * ncol - (pitch-nrow));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valarray[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch]);
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
  const auto valarray = this->valarray_;

  EXPECT_EQ(mat.getNrow(),  nrow);
  EXPECT_EQ(mat.getNcol(),  ncol);
  EXPECT_EQ(mat.getNelem(), nrow * ncol);
  EXPECT_EQ(mat.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(mat.getPitch(), pitch);

  EXPECT_TRUE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.getCapacity(), capacity);
  EXPECT_EQ(mat.getOffset(),   offset);

  EXPECT_EQ(mat.getNcol(), mat.getPitch());
  EXPECT_EQ(mat.getCapacity(), nrow * ncol);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valarray[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch + j]);
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
  const auto valarray = this->valarray_;

  EXPECT_EQ(mat.getNrow(),  nrow);
  EXPECT_EQ(mat.getNcol(),  ncol);
  EXPECT_EQ(mat.getNelem(), nrow * ncol);
  EXPECT_EQ(mat.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(mat.getPitch(), pitch);

  EXPECT_FALSE(mat.isShrunk());
  EXPECT_FALSE(mat.isSquare());

  EXPECT_EQ(mat.getCapacity(), capacity);
  EXPECT_EQ(mat.getOffset(),   offset);

  EXPECT_LT(mat.getNcol(), mat.getPitch());
  EXPECT_EQ(mat.getCapacity(), pitch * nrow - (pitch-ncol));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(mat(i, j), valarray[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch + j]);
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
