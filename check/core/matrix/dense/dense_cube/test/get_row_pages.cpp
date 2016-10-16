#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < rows; ++i ) {
        tmp.push(valarray[offset + (i+row0) + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0*pitch0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0*pitch0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0*pitch0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0*pitch0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0*pitch0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0*pitch0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetRowPages) {
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto subcube = cube.getRowPages({row0, row0+rows});

  EXPECT_EQ(subcube.getNrow(),    rows);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   npage);
  EXPECT_EQ(subcube.getNelem(),   rows * ncol * npage);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(rows, ncol, npage));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - row0*pitch0);
  EXPECT_EQ(subcube.getOffset(),   offset + row0*pitch0);

  EXPECT_EQ(subcube.getValue(),            &(cube(row0, 0, 0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i+row0, j, k));
      }
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < rows; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + (i+row0)*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
