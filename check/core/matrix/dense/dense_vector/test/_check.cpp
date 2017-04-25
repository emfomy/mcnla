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
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(vec.length(), length);
  EXPECT_EQ(vec.nelem(),  length);
  EXPECT_EQ(vec.stride(), stride);

  EXPECT_EQ(vec.sizes(),  std::make_tuple(length));

  EXPECT_TRUE(vec.isShrunk());

  EXPECT_EQ(vec.capacity(), capacity);
  EXPECT_EQ(vec.offset(),   offset);

  EXPECT_EQ(vec.capacity(), length);

  for ( auto i = 0; i < length; ++i ) {
    EXPECT_EQ(vec(i), valptr0[offset + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < length; ++i ) {
    tmp.push(valptr0[offset + i]);
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
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(vec.length(), length);
  EXPECT_EQ(vec.nelem(),  length);
  EXPECT_EQ(vec.stride(), stride);

  EXPECT_EQ(vec.sizes(),  std::make_tuple(length));

  EXPECT_FALSE(vec.isShrunk());

  EXPECT_EQ(vec.capacity(), capacity);
  EXPECT_EQ(vec.offset(),   offset);

  EXPECT_EQ(vec.capacity(), length * stride - (stride-1));

  for ( auto i = 0; i < length; ++i ) {
    EXPECT_EQ(vec(i), valptr0[offset + i*stride]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < length; ++i ) {
    tmp.push(valptr0[offset + i*stride]);
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
