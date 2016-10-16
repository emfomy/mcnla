#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0*pitch0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0*pitch0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0*pitch0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0*pitch0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0*pitch0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;
  const mcnla::index_t col0 = 2, cols = 3;

  auto block = cube.getCols(pageidx, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (col0 + pageidx*pitch0*pitch1));
  EXPECT_EQ(block.getOffset(),   offset + (col0 + pageidx*pitch0*pitch1));


  EXPECT_EQ(block.getValue(),            &(cube(0, col0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j+col0, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + (j+col0) + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
