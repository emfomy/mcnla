#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiagonalLower) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_TRUE(nrow > ncol);

  const mcnla::index_t idx = 3;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx);
  EXPECT_EQ(segment.getOffset(),   offset + idx);

  EXPECT_EQ(segment.getValue(),            &(mat(idx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiagonalLower) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_TRUE(nrow > ncol);

  const mcnla::index_t idx = 3;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx);
  EXPECT_EQ(segment.getOffset(),   offset + idx);

  EXPECT_EQ(segment.getValue(),            &(mat(idx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiagonalLower) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_TRUE(nrow > ncol);

  const mcnla::index_t idx = 3;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + idx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(idx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiagonalLower) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_TRUE(nrow > ncol);

  const mcnla::index_t idx = 3;

  auto segment = mat.getDiagonal(-idx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + idx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(idx, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i+idx, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
