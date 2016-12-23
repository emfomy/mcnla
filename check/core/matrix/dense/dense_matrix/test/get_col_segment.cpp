#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetColSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = mat({row0, row0+rows}, colidx);

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch));
  EXPECT_EQ(segment.getOffset(),   offset + row0 + colidx*pitch);

  EXPECT_EQ(segment.getValuePtr(), &(mat(row0, colidx)));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), mat(i+row0, colidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetColSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = mat({row0, row0+rows}, colidx);

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch));
  EXPECT_EQ(segment.getOffset(),   offset + row0 + colidx*pitch);

  EXPECT_EQ(segment.getValuePtr(), &(mat(row0, colidx)));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), mat(i+row0, colidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetColSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = mat({row0, row0+rows}, colidx);

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + row0*pitch + colidx);

  EXPECT_EQ(segment.getValuePtr(), &(mat(row0, colidx)));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), mat(i+row0, colidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetColSegment) {
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = mat({row0, row0+rows}, colidx);

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + row0*pitch + colidx);

  EXPECT_EQ(segment.getValuePtr(), &(mat(row0, colidx)));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), mat(i+row0, colidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
