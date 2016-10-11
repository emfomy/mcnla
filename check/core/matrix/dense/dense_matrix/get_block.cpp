#include "test.hpp"
#include <queue>

TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, GetBlock) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t row0 = 2, rows = 3;
  const mcnla::index_t col0 = 3, cols = 2;

  auto block = mat.getBlock({row0, row0+rows}, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),   rows);
  EXPECT_EQ(block.getNcol(),   cols);
  EXPECT_EQ(block.getNelem(),  rows * cols);
  EXPECT_EQ(block.getSizes(),  std::make_pair(rows, cols));
  EXPECT_EQ(block.getPitch(),  pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + col0*pitch));
  EXPECT_EQ(block.getOffset(),   row0 + col0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(row0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j+col0));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[(i+row0) + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[(i+row0) + (j+col0)*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, GetBlock) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t row0 = 2, rows = 3;
  const mcnla::index_t col0 = 3, cols = 2;

  auto block = mat.getBlock({row0, row0+rows}, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),   rows);
  EXPECT_EQ(block.getNcol(),   cols);
  EXPECT_EQ(block.getNelem(),  rows * cols);
  EXPECT_EQ(block.getSizes(),  std::make_pair(rows, cols));
  EXPECT_EQ(block.getPitch(),  pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0 + col0*pitch));
  EXPECT_EQ(block.getOffset(),   row0 + col0*pitch);

  EXPECT_EQ(block.getValue(),            &(mat(row0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j+col0));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[(i+row0) + (j+col0)*pitch]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto j = 0; j < cols; ++j ) {
    for ( auto i = 0; i < rows; ++i ) {
      tmp.push(valarray[(i+row0) + (j+col0)*pitch]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, GetBlock) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t row0 = 2, rows = 3;
  const mcnla::index_t col0 = 3, cols = 2;

  auto block = mat.getBlock({row0, row0+rows}, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),   rows);
  EXPECT_EQ(block.getNcol(),   cols);
  EXPECT_EQ(block.getNelem(),  rows * cols);
  EXPECT_EQ(block.getSizes(),  std::make_pair(rows, cols));
  EXPECT_EQ(block.getPitch(),  pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch + col0));
  EXPECT_EQ(block.getOffset(),   row0*pitch + col0);

  EXPECT_EQ(block.getValue(),            &(mat(row0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j+col0));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[(i+row0)*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[(i+row0)*pitch + (j+col0)]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, GetBlock) {
  auto pitch    = this->pitch_;
  auto capacity = this->capacity_;
  auto mat      = this->mat_;
  auto valarray = this->valarray_;

  const mcnla::index_t row0 = 2, rows = 3;
  const mcnla::index_t col0 = 3, cols = 2;

  auto block = mat.getBlock({row0, row0+rows}, {col0, col0+cols});

  EXPECT_EQ(block.getNrow(),   rows);
  EXPECT_EQ(block.getNcol(),   cols);
  EXPECT_EQ(block.getNelem(),  rows * cols);
  EXPECT_EQ(block.getSizes(),  std::make_pair(rows, cols));
  EXPECT_EQ(block.getPitch(),  pitch);

  EXPECT_FALSE(block.isShrunk());
  EXPECT_FALSE(block.isSquare());

  EXPECT_EQ(block.getCapacity(), capacity - (row0*pitch + col0));
  EXPECT_EQ(block.getOffset(),   row0*pitch + col0);

  EXPECT_EQ(block.getValue(),            &(mat(row0, col0)));
  EXPECT_EQ(&(block.getValueValarray()), &(mat.getValueValarray()));

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), mat(i+row0, j+col0));
    }
  }

  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      EXPECT_EQ(block(i, j), valarray[(i+row0)*pitch + (j+col0)]);
    }
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < rows; ++i ) {
    for ( auto j = 0; j < cols; ++j ) {
      tmp.push(valarray[(i+row0)*pitch + (j+col0)]);
    }
  }
  for ( auto value : block ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
