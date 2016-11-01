#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetCols) {
  const auto nrow     = this->nrow_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat.getCols({col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - col0*pitch);
  EXPECT_EQ(block.getOffset(),   offset + col0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat.getCols({col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - col0*pitch);
  EXPECT_EQ(block.getOffset(),   offset + col0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < nrow; ++i ) {
      tmp.push(valarray[offset + i + (j+col0)*pitch]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat.getCols({col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - col0);
  EXPECT_EQ(block.getOffset(),   offset + col0);

  EXPECT_EQ(block.getValue(),            &(mat(0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch + (j+col0)]);
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
  const auto valarray = this->valarray_;

  const mcnla::index_t col0 = 2, cols = 3;

  auto block = mat.getCols({col0, col0+cols});

  EXPECT_EQ(block.getNrow(),  nrow);
  EXPECT_EQ(block.getNcol(),  cols);
  EXPECT_EQ(block.getNelem(), nrow * cols);
  EXPECT_EQ(block.getSizes(), std::make_pair(nrow, cols));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - col0);
  EXPECT_EQ(block.getOffset(),   offset + col0);

  EXPECT_EQ(block.getValue(),            &(mat(0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i, j+col0));
    }
  }

  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + i*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < nrow; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[offset + i*pitch + (j+col0)]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}