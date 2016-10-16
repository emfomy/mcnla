#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * ncol;

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), valarray[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + j*pitch]);
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


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  auto segment = mat.vectorize();

  const auto idxs = pitch * ncol - (pitch-nrow);

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), mat(i, j));
    }
  }

  for ( auto i = 0; i < pitch; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      if ( i >= nrow && j == ncol-1 ) break;
      EXPECT_EQ(segment(i + j*pitch), valarray[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < pitch; ++i ) {
      if ( i >= nrow && j == ncol-1 ) break;
      tmp.push(valarray[offset + i + j*pitch]);
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


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * ncol;

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), valarray[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + i*pitch + j]);
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


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * pitch - (pitch-ncol);

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity);
  EXPECT_EQ(segment.getOffset(),   offset);

  EXPECT_EQ(segment.getValue(),            &(mat(0, 0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch; ++j ) {
      if ( i == nrow-1 && j >= ncol ) break;
      EXPECT_EQ(segment(i*pitch + j), valarray[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch; ++j ) {
      if ( i == nrow-1 && j >= ncol ) break;
      tmp.push(valarray[offset + i*pitch + j]);
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
