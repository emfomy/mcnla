#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx) + i*pitch0 + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetDiagonalBottom) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  ASSERT_GT(nrow, ncol);

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t idx = 6;

  auto segment = cube.getDiagonal(pageidx, -idx);

  EXPECT_EQ(segment.getLength(), nrow-idx);
  EXPECT_EQ(segment.getNelem(),  nrow-idx);
  EXPECT_EQ(segment.getSizes(),  nrow-idx);
  EXPECT_EQ(segment.getStride(), pitch0+1);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - (idx*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(segment.getOffset(),   offset + (idx*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(segment.getValue(),            &(cube(idx, 0, pageidx)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), cube(i+idx, i, pageidx));
  }

  for ( auto i = 0; i < nrow-idx; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow-idx; ++i ) {
    tmp.push(valarray[offset + (i+idx)*pitch0 + i + pageidx*pitch0*pitch1]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
