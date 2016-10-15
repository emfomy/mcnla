#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + col0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx + (i+col0)*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetRowSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto segment = cube.getRowSegment(rowidx, pageidx, {col0, col0+cols});

  EXPECT_EQ(segment.getLength(), cols);
  EXPECT_EQ(segment.getNelem(),  cols);
  EXPECT_EQ(segment.getSizes(),  cols);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + col0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(rowidx, col0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i+col0, pageidx));
  }

  for ( auto i = 0; i < cols; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < cols; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + (i+col0) + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
