#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx + colidx*pitch0));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx + colidx*pitch0));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx + colidx*pitch0 + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetTube) {
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t rowidx = 3;
  const mcnla::index_t colidx = 2;

  auto segment = cube.getTube(rowidx, colidx);

  EXPECT_EQ(segment.getLength(), npage);
  EXPECT_EQ(segment.getNelem(),  npage);
  EXPECT_EQ(segment.getSizes(),  npage);
  EXPECT_EQ(segment.getStride(), pitch0*pitch1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (rowidx*pitch0 + colidx));
  EXPECT_EQ(segment.getOffset(),   offset + (rowidx*pitch0 + colidx));

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), cube(rowidx, colidx, i));
  }

  for ( auto i = 0; i < npage; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < npage; ++i ) {
    tmp.push(valarray[offset + rowidx*pitch0 + colidx + i*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
