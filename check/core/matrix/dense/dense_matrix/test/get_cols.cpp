#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat(""_, {col0, col0+cols});

  EXPECT_EQ(block.nrow(),  nrow);
  EXPECT_EQ(block.ncol(),  cols);
  EXPECT_EQ(block.nelem(), nrow * cols);
  EXPECT_EQ(block.pitch(), pitch);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.capacity(), capacity - col0*pitch);
  EXPECT_EQ(block.offset(),   offset + col0*pitch);

  EXPECT_EQ(block.valPtr(), &(mat(0, col0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valptr0[offset + i + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valptr0[offset + i + (j+col0)*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat(""_, {col0, col0+cols});

  EXPECT_EQ(block.nrow(),  nrow);
  EXPECT_EQ(block.ncol(),  cols);
  EXPECT_EQ(block.nelem(), nrow * cols);
  EXPECT_EQ(block.pitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.capacity(), capacity - col0*pitch);
  EXPECT_EQ(block.offset(),   offset + col0*pitch);

  EXPECT_EQ(block.valPtr(), &(mat(0, col0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valptr0[offset + i + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valptr0[offset + i + (j+col0)*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat(""_, {col0, col0+cols});

  EXPECT_EQ(block.nrow(),  nrow);
  EXPECT_EQ(block.ncol(),  cols);
  EXPECT_EQ(block.nelem(), nrow * cols);
  EXPECT_EQ(block.pitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.capacity(), capacity - col0);
  EXPECT_EQ(block.offset(),   offset + col0);

  EXPECT_EQ(block.valPtr(), &(mat(0, col0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valptr0[offset + i*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valptr0[offset + i*pitch + (j+col0)]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valptr0  = this->valptr0_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat(""_, {col0, col0+cols});

  EXPECT_EQ(block.nrow(),  nrow);
  EXPECT_EQ(block.ncol(),  cols);
  EXPECT_EQ(block.nelem(), nrow * cols);
  EXPECT_EQ(block.pitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.capacity(), capacity - col0);
  EXPECT_EQ(block.offset(),   offset + col0);

  EXPECT_EQ(block.valPtr(), &(mat(0, col0)));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valptr0[offset + i*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valptr0[offset + i*pitch + (j+col0)]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
