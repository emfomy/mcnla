#define MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto block = mat.getRows({row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - row0);
  EXPECT_EQ(block.getOffset(),   offset + row0);

  EXPECT_EQ(block.getValue(),            &(mat(row0, 0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto block = mat.getRows({row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - row0);
  EXPECT_EQ(block.getOffset(),   offset + row0);

  EXPECT_EQ(block.getValue(),            &(mat(row0, 0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0) + j*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < ncol; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[offset + (i+row0) + j*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto block = mat.getRows({row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_TRUE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - row0*pitch);
  EXPECT_EQ(block.getOffset(),   offset + row0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(row0, 0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch + j]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetRows) {
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto mat      = this->mat_;
  const auto valarray = this->valarray_;

  const mcnla::index_t row0 = 3, rows = 5;

  auto block = mat.getRows({row0, row0+rows});

  EXPECT_EQ(block.getNrow(),  rows);
  EXPECT_EQ(block.getNcol(),  ncol);
  EXPECT_EQ(block.getNelem(), rows * ncol);
  EXPECT_EQ(block.getSizes(), std::make_pair(rows, ncol));
  EXPECT_EQ(block.getPitch(), pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_TRUE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - row0*pitch);
  EXPECT_EQ(block.getOffset(),   offset + row0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(row0, 0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      EXPECT_EQ(block(i, j), valarray[offset + (i+row0)*pitch + j]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < ncol; ++j ) {
      tmp.push(valarray[offset + (i+row0)*pitch + j]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
