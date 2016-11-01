#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetDiagonal) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiagonal();

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + i + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetDiagonal) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiagonal();

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + i*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + i + i*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetDiagonal) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiagonal();

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + i*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetDiagonal) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  auto segment = mat.getDiagonal();

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), mat(i, i));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + i*pitch + i]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}