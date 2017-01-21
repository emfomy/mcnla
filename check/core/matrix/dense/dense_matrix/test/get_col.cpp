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

  auto segment = mat("", colidx);

  EXPECT_EQ(segment.length(), nrow);
  EXPECT_EQ(segment.nelem(),  nrow);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.offset(),   offset + colidx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(0, colidx)));

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

  auto segment = mat("", colidx);

  EXPECT_EQ(segment.length(), nrow);
  EXPECT_EQ(segment.nelem(),  nrow);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - colidx*pitch);
  EXPECT_EQ(segment.offset(),   offset + colidx*pitch);

  EXPECT_EQ(segment.valPtr(), &(mat(0, colidx)));

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

  auto segment = mat("", colidx);

  EXPECT_EQ(segment.length(), nrow);
  EXPECT_EQ(segment.nelem(),  nrow);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - colidx);
  EXPECT_EQ(segment.offset(),   offset + colidx);

  EXPECT_EQ(segment.valPtr(), &(mat(0, colidx)));

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

  auto segment = mat("", colidx);

  EXPECT_EQ(segment.length(), nrow);
  EXPECT_EQ(segment.nelem(),  nrow);
  EXPECT_EQ(segment.stride(), pitch);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity - colidx);
  EXPECT_EQ(segment.offset(),   offset + colidx);

  EXPECT_EQ(segment.valPtr(), &(mat(0, colidx)));

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
