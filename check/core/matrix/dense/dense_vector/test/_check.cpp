#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseVectorTest, Check) {
}

TYPED_TEST(DenseVectorTest_Size8_Stride1, Check) {
  const auto length   = this->length_;
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(vec.getLength(), length);
  EXPECT_EQ(vec.getNelem(),  length);
  EXPECT_EQ(vec.getStride(), stride);

  EXPECT_EQ(vec.getSizes(),  std::make_tuple(length));

  EXPECT_TRUE(vec.isShrunk());

  EXPECT_EQ(vec.getCapacity(), capacity);
  EXPECT_EQ(vec.getOffset(),   offset);

  EXPECT_EQ(vec.getCapacity(), length);

  for ( auto i = 0; i < length; ++i ) {
    EXPECT_EQ(vec(i), valarray[offset + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < length; ++i ) {
    tmp.push(valarray[offset + i]);
  }
  for ( auto value : vec ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : vec ) {
    EXPECT_NE(value, TypeParam(0));
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride3, Check) {
  const auto length   = this->length_;
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valarray = this->valarray_;

  EXPECT_EQ(vec.getLength(), length);
  EXPECT_EQ(vec.getNelem(),  length);
  EXPECT_EQ(vec.getStride(), stride);

  EXPECT_EQ(vec.getSizes(),  std::make_tuple(length));

  EXPECT_FALSE(vec.isShrunk());

  EXPECT_EQ(vec.getCapacity(), capacity);
  EXPECT_EQ(vec.getOffset(),   offset);

  EXPECT_EQ(vec.getCapacity(), length * stride - (stride-1));

  for ( auto i = 0; i < length; ++i ) {
    EXPECT_EQ(vec(i), valarray[offset + i*stride]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < length; ++i ) {
    tmp.push(valarray[offset + i*stride]);
  }
  for ( auto value : vec ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);

  for ( auto value : vec ) {
    EXPECT_NE(value, TypeParam(0));
  }
}
