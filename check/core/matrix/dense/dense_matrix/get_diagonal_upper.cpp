#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiagonalUpper) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.getLength(), ncol-idx);
  EXPECT_EQ(segment.getNelem(),  ncol-idx);
  EXPECT_EQ(segment.getSizes(),  ncol-idx);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + idx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, idx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + (i+idx)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valarray[offset + i + (i+idx)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiagonalUpper) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.getLength(), ncol-idx);
  EXPECT_EQ(segment.getNelem(),  ncol-idx);
  EXPECT_EQ(segment.getSizes(),  ncol-idx);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + idx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, idx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + (i+idx)*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valarray[offset + i + (i+idx)*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiagonalUpper) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.getLength(), ncol-idx);
  EXPECT_EQ(segment.getNelem(),  ncol-idx);
  EXPECT_EQ(segment.getSizes(),  ncol-idx);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx);
  EXPECT_EQ(segment.getOffset(),   offset + idx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, idx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + (i+idx)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valarray[offset + i*pitch + (i+idx)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiagonalUpper) {
  auto nrow     = this->nrow_;
  auto ncol     = this->ncol_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto offset   = this->offset_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t idx = 2;

  auto segment = mat.getDiagonal(idx);

  EXPECT_EQ(segment.getLength(), ncol-idx);
  EXPECT_EQ(segment.getNelem(),  ncol-idx);
  EXPECT_EQ(segment.getSizes(),  ncol-idx);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx);
  EXPECT_EQ(segment.getOffset(),   offset + idx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, idx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i+idx));
  }

  for ( auto i = 0; i < ncol-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + (i+idx)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol-idx; ++i ) {
    tmp.push(valarray[offset + i*pitch + (i+idx)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
