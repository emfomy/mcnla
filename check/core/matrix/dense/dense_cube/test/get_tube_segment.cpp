#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetTubeSegment) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;
  const mcnla::index_t page0 = 5, pages = 2;

  auto segment = cube.getTubeSegment(rowidx, colidx, {page0, page0+pages});

  EXPECT_EQ(segment.getLength(), pages);
  EXPECT_EQ(segment.getNelem(),  pages);
  EXPECT_EQ(segment.getSizes(),  pages);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx + page0*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx + page0*pitch0*pitch1));

  EXPECT_EQ(segment.getValuePtr(),            &(cube(rowidx, colidx, page0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i+page0));
  }

  for ( auto i = 0; i < pages; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < pages; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + (i+page0)*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
