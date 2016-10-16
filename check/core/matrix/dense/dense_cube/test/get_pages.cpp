#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_TRUE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < nrow; ++i ) {
        tmp.push(valarray[offset + i + j*pitch0 + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_TRUE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, GetPages) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  const mcnla::index_t page0 = 5, pages = 2;

  auto subcube = cube.getPages({page0, page0+pages});

  EXPECT_EQ(subcube.getNrow(),    nrow);
  EXPECT_EQ(subcube.getNcol(),    ncol);
  EXPECT_EQ(subcube.getNpage(),   pages);
  EXPECT_EQ(subcube.getNelem(),   nrow * ncol * pages);
  EXPECT_EQ(subcube.getSizes(),   std::make_tuple(nrow, ncol, pages));
  EXPECT_EQ(subcube.getPitch0(),  pitch0);
  EXPECT_EQ(subcube.getPitch1(),  pitch1);
  EXPECT_EQ(subcube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(subcube.isShrunk());

  EXPECT_EQ(subcube.getCapacity(), capacity - page0*pitch0*pitch1);
  EXPECT_EQ(subcube.getOffset(),   offset + page0*pitch0*pitch1);

  EXPECT_EQ(subcube.getValue(),            &(cube(0, 0, page0)));
  EXPECT_EQ(&(subcube.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), cube(i, j, k+page0));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < pages; ++k ) {
        EXPECT_EQ(subcube(i, j, k), valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < pages; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < ncol; ++j ) {
        tmp.push(valarray[offset + i*pitch0 + j + (k+page0)*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : subcube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
