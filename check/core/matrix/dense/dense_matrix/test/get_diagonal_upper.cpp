#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiagonalUpper) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.len(),    ncol-idx);
  EXPECT_EQ(segment.nelem(),  ncol-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.offset(),   offset + idx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(0, idx)));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i + (i+idx)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valptr0[offset + i + (i+idx)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiagonalUpper) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.len(),    ncol-idx);
  EXPECT_EQ(segment.nelem(),  ncol-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.offset(),   offset + idx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(0, idx)));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i + (i+idx)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valptr0[offset + i + (i+idx)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiagonalUpper) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.len(),    ncol-idx);
  EXPECT_EQ(segment.nelem(),  ncol-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx);
  EXPECT_EQ(segment.offset(),   offset + idx);

  EXPECT_EQ(segment.valPtr(), &(mat(0, idx)));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i*pitch + (i+idx)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valptr0[offset + i*pitch + (i+idx)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiagonalUpper) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.len(),    ncol-idx);
  EXPECT_EQ(segment.nelem(),  ncol-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx);
  EXPECT_EQ(segment.offset(),   offset + idx);

  EXPECT_EQ(segment.valPtr(), &(mat(0, idx)));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + i*pitch + (i+idx)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valptr0[offset + i*pitch + (i+idx)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
