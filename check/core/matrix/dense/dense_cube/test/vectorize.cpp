#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x5, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = nrow * ncol * npage;

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch8x10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = nrow * pitch1 * npage - nrow * (pitch1-ncol);

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( j >= ncol && k == npage-1 ) break;
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
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
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x5, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = pitch0 * ncol * npage - (pitch0-nrow);

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch0; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( i >= nrow && j == ncol-1 && k == npage-1 ) break;
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto i = 0; i < pitch0; ++i ) {
        if ( i >= nrow && j == ncol-1 && k == npage-1 ) break;
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_ColMajor_Size8x5x7_Pitch10x10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = pitch0 * pitch1 * npage - pitch0 * (pitch1-ncol) - (pitch0-nrow);

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch0; ++i ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( j >= ncol && k == npage-1 ) break;
        if ( i >= nrow && j == ncol-1 && k == npage-1 ) break;
        EXPECT_EQ(segment(i + j*pitch0 + k*pitch0*pitch1), valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto j = 0; j < pitch1; ++j ) {
      if ( j >= ncol && k == npage-1 ) break;
      for ( auto i = 0; i < pitch0; ++i ) {
        if ( i >= nrow && j == ncol-1 && k == npage-1 ) break;
        tmp.push(valarray[offset + i + j*pitch0 + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x8, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = nrow * ncol * npage;

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch5x10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = pitch1 * ncol * npage - (pitch1-nrow) * ncol;

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch1; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( i >= nrow && k == npage-1 ) break;
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
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
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x8, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = nrow * pitch0 * npage - (pitch0-ncol);

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch0; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( j >= ncol && i == nrow-1 && k == npage-1 ) break;
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < nrow; ++i ) {
      for ( auto j = 0; j < pitch0; ++j ) {
        if ( j >= ncol && i == nrow-1 && k == npage-1 ) break;
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}


TYPED_TEST(DenseCubeTest_RowMajor_Size8x5x7_Pitch10x10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto npage    = this->npage_;
  const auto pitch0   = this->pitch0_;
  const auto pitch1   = this->pitch1_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto cube     = this->cube_;
  const auto valarray = this->valarray_;

  auto segment = cube.vectorize();

  const auto idxs = pitch1 * pitch0 * npage - (pitch1-nrow) * pitch0 - (pitch0-ncol);

  EXPECT_EQ(idxs, &(cube(nrow-1, ncol-1, npage-1)) - &(cube(0, 0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(cube(0, 0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(cube.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), cube(i, j, k));
      }
    }
  }

  for ( auto i = 0; i < pitch1; ++i ) {
    for ( auto j = 0; j < pitch0; ++j ) {
      for ( auto k = 0; k < npage; ++k ) {
        if ( i >= nrow && k == npage-1 ) break;
        if ( j >= ncol && i == nrow-1 && k == npage-1 ) break;
        EXPECT_EQ(segment(i*pitch0 + j + k*pitch0*pitch1), valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto k = 0; k < npage; ++k ) {
    for ( auto i = 0; i < pitch1; ++i ) {
      if ( i >= nrow && k == npage-1 ) break;
      for ( auto j = 0; j < pitch0; ++j ) {
        if ( j >= ncol && i == nrow-1 && k == npage-1 ) break;
        tmp.push(valarray[offset + i*pitch0 + j + k*pitch0*pitch1]);
      }
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valarray[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valarray[offset + idxs]));
}
