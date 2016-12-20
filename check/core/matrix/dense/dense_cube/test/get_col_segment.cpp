#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0 + colidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0) + colidx*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch0 + colidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0*pitch0 + colidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch0 + colidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0*pitch0 + colidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch0 + colidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0*pitch0 + colidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetColSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t colidx  = 2;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto segment = cube.getColSegment(colidx, pageidx, {row0, row0+rows});

  EXPECT_EQ(segment.getLength(), rows);
  EXPECT_EQ(segment.getNelem(),  rows);
  EXPECT_EQ(segment.getSizes(),  rows);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (row0*pitch0 + colidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (row0*pitch0 + colidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),          &(cube(row0, colidx, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), cube(i+row0, colidx, pageidx));
  }

  for ( auto i = 0; i < rows; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    tmp.push(valarray[offset + (i+row0)*pitch0 + colidx + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
