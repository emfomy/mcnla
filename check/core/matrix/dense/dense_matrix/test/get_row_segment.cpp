#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetRowSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.len(),    cols);
  EXPECT_EQ(segment.nelem(),  cols);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - (rowidx + col0*pitch));
  EXPECT_EQ(segment.offset(),   offset + rowidx + col0*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, col0)));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx + (i+col0)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valptr0[offset + rowidx + (i+col0)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetRowSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.len(),    cols);
  EXPECT_EQ(segment.nelem(),  cols);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - (rowidx + col0*pitch));
  EXPECT_EQ(segment.offset(),   offset + rowidx + col0*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, col0)));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx + (i+col0)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valptr0[offset + rowidx + (i+col0)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetRowSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.len(),    cols);
  EXPECT_EQ(segment.nelem(),  cols);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - (rowidx*pitch + col0));
  EXPECT_EQ(segment.offset(),   offset + rowidx*pitch + col0);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, col0)));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx*pitch + (i+col0)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valptr0[offset + rowidx*pitch + (i+col0)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetRowSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.len(),    cols);
  EXPECT_EQ(segment.nelem(),  cols);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - (rowidx*pitch + col0));
  EXPECT_EQ(segment.offset(),   offset + rowidx*pitch + col0);

  EXPECT_EQ(segment.valPtr(), &(mat(rowidx, col0)));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valptr0[offset + rowidx*pitch + (i+col0)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valptr0[offset + rowidx*pitch + (i+col0)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
