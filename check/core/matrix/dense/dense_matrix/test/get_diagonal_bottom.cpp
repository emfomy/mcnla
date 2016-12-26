#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 6;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.length(), nrow-idx);
  EXPECT_EQ(segment.nelem(),  nrow-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx);
  EXPECT_EQ(segment.offset(),   offset + idx);

  EXPECT_EQ(segment.valuePtr(), &(mat(idx, 0)));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 6;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.length(), nrow-idx);
  EXPECT_EQ(segment.nelem(),  nrow-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx);
  EXPECT_EQ(segment.offset(),   offset + idx);

  EXPECT_EQ(segment.valuePtr(), &(mat(idx, 0)));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 6;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.length(), nrow-idx);
  EXPECT_EQ(segment.nelem(),  nrow-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.offset(),   offset + idx*pitch);

  EXPECT_EQ(segment.valuePtr(), &(mat(idx, 0)));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 6;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.length(), nrow-idx);
  EXPECT_EQ(segment.nelem(),  nrow-idx);
  EXPECT_EQ(segment.stride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.offset(),   offset + idx*pitch);

  EXPECT_EQ(segment.valuePtr(), &(mat(idx, 0)));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
