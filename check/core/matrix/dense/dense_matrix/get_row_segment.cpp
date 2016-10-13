#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetRowSegment) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat.getRowSegment(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch));
  EXPECT_EQ(segment.getOffset(),   offset + rowidx + col0*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, col0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetRowSegment) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat.getRowSegment(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch));
  EXPECT_EQ(segment.getOffset(),   offset + rowidx + col0*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, col0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetRowSegment) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat.getRowSegment(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch + col0));
  EXPECT_EQ(segment.getOffset(),   offset + rowidx*pitch + col0);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, col0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch + (i+col0)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch + (i+col0)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetRowSegment) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = mat.getRowSegment(rowidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch + col0));
  EXPECT_EQ(segment.getOffset(),   offset + rowidx*pitch + col0);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, col0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i+col0));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch + (i+col0)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch + (i+col0)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
