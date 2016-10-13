#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat.getRow(rowidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rowidx);
  EXPECT_EQ(segment.getOffset(),   offset + rowidx);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat.getRow(rowidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rowidx);
  EXPECT_EQ(segment.getOffset(),   offset + rowidx);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat.getRow(rowidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rowidx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + rowidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch + i]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;

  auto segment = mat.getRow(rowidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rowidx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + rowidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(rowidx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(rowidx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
