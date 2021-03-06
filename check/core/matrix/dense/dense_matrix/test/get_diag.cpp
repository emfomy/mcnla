#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiag) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiag();

  EXPECT_EQ(segment.len(),    ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + i + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiag) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiag();

  EXPECT_EQ(segment.len(),    ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + i + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiag) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiag();

  EXPECT_EQ(segment.len(),    ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + i*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiag) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiag();

  EXPECT_EQ(segment.len(),    ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + i*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
