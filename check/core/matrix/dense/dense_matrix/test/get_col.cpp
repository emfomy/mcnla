#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetCol) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + colidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[offset + i + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetCol) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.getOffset(),   offset + colidx*pitch);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i + colidx*pitch]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[offset + i + colidx*pitch]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetCol) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx);
  EXPECT_EQ(segment.getOffset(),   offset + colidx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[offset + i*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetCol) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx = 2;

  auto segment = mat.getCol(colidx);

  EXPECT_EQ(segment.getLength(), nrow);
  EXPECT_EQ(segment.getNelem(),  nrow);
  EXPECT_EQ(segment.getSizes(),  nrow);
  EXPECT_EQ(segment.getStride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - colidx);
  EXPECT_EQ(segment.getOffset(),   offset + colidx);

  EXPECT_EQ(segment.getValue(),            &(mat(0, colidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), mat(i, colidx));
  }

  for ( auto i = 0; i < nrow; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + i*pitch + colidx]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    tmp.push(valarray[offset + i*pitch + colidx]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
