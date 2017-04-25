#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat(rowidx, ""_);

  EXPECT_EQ(segment.length(), ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - rowidx);
  EXPECT_EQ(segment.offset(),   offset + rowidx);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + rowidx + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat(rowidx, ""_);

  EXPECT_EQ(segment.length(), ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - rowidx);
  EXPECT_EQ(segment.offset(),   offset + rowidx);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + rowidx + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat(rowidx, ""_);

  EXPECT_EQ(segment.length(), ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - rowidx*pitch);
  EXPECT_EQ(segment.offset(),   offset + rowidx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + rowidx*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat(rowidx, ""_);

  EXPECT_EQ(segment.length(), ncol);
  EXPECT_EQ(segment.nelem(),  ncol);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - rowidx*pitch);
  EXPECT_EQ(segment.offset(),   offset + rowidx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, 0)));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valptr0[offset + rowidx*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
