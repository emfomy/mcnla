#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch0 + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetPage) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t pageidx = 5;

  auto block = cube.getPage(pageidx);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), nrow * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - pageidx*pitch0*pitch1);
  EXPECT_EQ(block.getOffset(),   offset + pageidx*pitch0*pitch1);

  EXPECT_EQ(block.getValue(),            &(cube(0, 0, pageidx)));
  EXPECT_EQ(&(block.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), cube(i, j, pageidx));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch0 + j + pageidx*pitch0*pitch1]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
