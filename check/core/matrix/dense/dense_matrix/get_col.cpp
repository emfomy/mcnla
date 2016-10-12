#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetCol) {
  auto nrow     = this->nrow_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t colidx = 3;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.getOffset(),   colidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[i + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[i + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetCol) {
  auto nrow     = this->nrow_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t colidx = 3;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.getOffset(),   colidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[i + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[i + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetCol) {
  auto nrow     = this->nrow_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t colidx = 3;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx);
  EXPECT_EQ(segment.getOffset(),   colidx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[i*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[i*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetCol) {
  auto nrow     = this->nrow_;
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t colidx = 3;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx);
  EXPECT_EQ(segment.getOffset(),   colidx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[i*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[i*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
