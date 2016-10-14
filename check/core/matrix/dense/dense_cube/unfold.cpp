#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto cols = ncol * npage;

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto cols = pitch1 * npage - (pitch1-ncol);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * (cols));
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( j >= ncol && k == npage-1 ) break;
        EXPECT_EQ(block(i, j + k*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      if ( j >= ncol && k == npage-1 ) break;
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto cols = ncol * npage;

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto cols = pitch1 * npage - (pitch1-ncol);

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * (cols));
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i, j + k*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( j >= ncol && k == npage-1 ) break;
        EXPECT_EQ(block(i, j + k*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      if ( j >= ncol && k == npage-1 ) break;
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto rows = nrow * npage;

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto rows = pitch1 * npage - (pitch1-nrow);

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch1; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( i >= nrow && k == npage-1 ) break;
        EXPECT_EQ(block(i + k*pitch1, j), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < pitch1; ++i ) {
      if ( i >= nrow && k == npage-1 ) break;
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto rows = nrow * npage;

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, Unfold) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto block = cube.unfold();

  const auto rows = pitch1 * npage - (pitch1-nrow);

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch0);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity);
  EXPECT_EQ(block.getOffset(),   offset);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(block(i + k*pitch1, j), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch1; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( i >= nrow && k == npage-1 ) break;
        EXPECT_EQ(block(i + k*pitch1, j), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < pitch1; ++i ) {
      if ( i >= nrow && k == npage-1 ) break;
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
