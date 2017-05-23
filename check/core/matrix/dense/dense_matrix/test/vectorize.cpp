#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * ncol;

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.len(),    idxs);
  EXPECT_EQ(segment.nelem(),  idxs);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), valptr0[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valptr0[offset + i + j*pitch]);
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valptr0[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valptr0[offset + idxs]));
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  auto segment = mat.vectorize();

  const auto idxs = pitch * ncol - (pitch-nrow);

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.len(),    idxs);
  EXPECT_EQ(segment.nelem(),  idxs);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i + j*pitch), mat(i, j));
    }
  }

  for ( auto i = 0; i < pitch; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      if ( i >= nrow && j == ncol-1 ) break;
      EXPECT_EQ(segment(i + j*pitch), valptr0[offset + i + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < pitch; ++i ) {
      if ( i >= nrow && j == ncol-1 ) break;
      tmp.push(valptr0[offset + i + j*pitch]);
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valptr0[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valptr0[offset + idxs]));
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * ncol;

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.len(),    idxs);
  EXPECT_EQ(segment.nelem(),  idxs);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), valptr0[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valptr0[offset + i*pitch + j]);
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valptr0[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valptr0[offset + idxs]));
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, Vectorize) {
  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  auto segment = mat.vectorize();

  const auto idxs = nrow * pitch - (pitch-ncol);

  EXPECT_EQ(idxs, &(mat(nrow-1, ncol-1)) - &(mat(0, 0)) + 1);

  EXPECT_EQ(segment.len(),    idxs);
  EXPECT_EQ(segment.nelem(),  idxs);
  EXPECT_EQ(segment.stride(), 1);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.capacity(), capacity);
  EXPECT_EQ(segment.offset(),   offset);

  EXPECT_EQ(segment.valPtr(), &(mat(0, 0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(segment(i*pitch + j), mat(i, j));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch; ++j ) {
      if ( i == nrow-1 && j >= ncol ) break;
      EXPECT_EQ(segment(i*pitch + j), valptr0[offset + i*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < pitch; ++j ) {
      if ( i == nrow-1 && j >= ncol ) break;
      tmp.push(valptr0[offset + i*pitch + j]);
    }
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  auto ptr = &(valptr0[offset]);
  for ( auto value : segment ) {
    EXPECT_EQ(value, *ptr);
    ++ptr;
  }
  EXPECT_EQ(ptr, &(valptr0[offset + idxs]));
}
