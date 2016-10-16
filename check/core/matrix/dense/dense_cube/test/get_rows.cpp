#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t row0 = 3, rows = 5;

  auto block = cube.getRows(pageidx, {row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (row0*pitch0 + pageidx*pitch0*pitch1));

  EXPECT_EQ(block.getValue(),            &(cube(row0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i+row0, j, pageidx));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
