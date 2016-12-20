#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), pitch0);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetRow) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx  = 3;
  const mcnla::index_t pageidx = 5;

  auto segment = cube.getRow(rowidx, pageidx);

  EXPECT_EQ(segment.getLength(), ncol);
  EXPECT_EQ(segment.getNelem(),  ncol);
  EXPECT_EQ(segment.getSizes(),  ncol);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, i, pageidx));
  }

  for ( auto i = 0; i < ncol; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < ncol; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
