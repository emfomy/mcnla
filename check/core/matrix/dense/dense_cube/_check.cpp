#include "test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_TRUE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_EQ(cube.getNrow(), cube.getPitch0());
  EXPECT_EQ(cube.getNcol(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), nrow * ncol * npage);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_EQ(cube.getNrow(), cube.getPitch0());
  EXPECT_LT(cube.getNcol(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), nrow * pitch1 * npage - nrow * (pitch1-ncol));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_LT(cube.getNrow(), cube.getPitch0());
  EXPECT_EQ(cube.getNcol(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), pitch0 * ncol * npage - (pitch0-nrow));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_LT(cube.getNrow(), cube.getPitch0());
  EXPECT_LT(cube.getNcol(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), pitch0 * pitch1 * npage - pitch0 * (pitch1-ncol) - (pitch0-nrow));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_TRUE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_EQ(cube.getNcol(), cube.getPitch0());
  EXPECT_EQ(cube.getNrow(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), nrow * ncol * npage);

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_EQ(cube.getNcol(), cube.getPitch0());
  EXPECT_LT(cube.getNrow(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), ncol * pitch1 * npage - ncol * (pitch1-nrow));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_LT(cube.getNcol(), cube.getPitch0());
  EXPECT_EQ(cube.getNrow(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), pitch0 * nrow * npage - (pitch0-ncol));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, Check) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(cube.getNrow(),    nrow);
  EXPECT_EQ(cube.getNcol(),    ncol);
  EXPECT_EQ(cube.getNpage(),   npage);
  EXPECT_EQ(cube.getNelem(),   nrow * ncol * npage);
  EXPECT_EQ(cube.getSizes(),   std::make_tuple(nrow, ncol, npage));
  EXPECT_EQ(cube.getPitch0(),  pitch0);
  EXPECT_EQ(cube.getPitch1(),  pitch1);
  EXPECT_EQ(cube.getPitches(), std::make_pair(pitch0, pitch1));

  EXPECT_FALSE(cube.isShrunk());

  EXPECT_EQ(cube.getCapacity(), capacity);
  EXPECT_EQ(cube.getOffset(),   offset);

  EXPECT_LT(cube.getNcol(), cube.getPitch0());
  EXPECT_LT(cube.getNrow(), cube.getPitch1());
  EXPECT_EQ(cube.getCapacity(), pitch0 * pitch1 * npage - pitch0 * (pitch1-nrow) - (pitch0-ncol));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(cube(i, j, k), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : cube ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
