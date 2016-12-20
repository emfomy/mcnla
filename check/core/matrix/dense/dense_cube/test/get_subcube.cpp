#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0 + col0*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0 + col0*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0 + col0*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0 + col0*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0 + col0*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0 + col0*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0 + col0*pitch0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0 + col0*pitch0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + (j+col0)*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0*pitch0 + col0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0*pitch0 + col0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < cols; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0*pitch0 + col0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0*pitch0 + col0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < cols; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0*pitch0 + col0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0*pitch0 + col0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < cols; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetSubcube) {
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3,  rows = 5;
  const mcnla::index_t col0 = 2,  cols = 3;
  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getSubcube({row0, row0+rows}, {col0, col0+cols}, {page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    cols);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   rows * cols * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, cols, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - (row0*pitch0 + col0 + page0*pitch0*pitch1));
  EXPECT_EQ(subcube.getOffset(),   offset + (row0*pitch0 + col0 + page0*pitch0*pitch1));

  EXPECT_EQ(subcube.getValuePtr(),            &(cube(row0, col0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j+col0, k+page0));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < cols; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + (j+col0) + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
