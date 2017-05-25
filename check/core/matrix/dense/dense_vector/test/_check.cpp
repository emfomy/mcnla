#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseVectorTest, Check) {
}

TYPED_TEST(DenseVectorTest_Size8_Stride1, Check) {
  const auto len      = this->len_;
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(vec.len(),    len);
  EXPECT_EQ(vec.nelem(),  len);
  EXPECT_EQ(vec.stride(), stride);

  EXPECT_EQ(vec.sizes(),  std::make_tuple(len));

  EXPECT_TRUE(vec.isShrunk());

  EXPECT_EQ(vec.capacity(), capacity);
  EXPECT_EQ(vec.offset(),   offset);

  EXPECT_EQ(vec.capacity(), len);

  for ( auto i = 0; i < len; ++i ) {
    EXPECT_EQ(vec(i), valptr0[offset + i]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < len; ++i ) {
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
  const auto len      = this->len_;
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valptr0  = this->valptr0_;

  EXPECT_EQ(vec.len(),    len);
  EXPECT_EQ(vec.nelem(),  len);
  EXPECT_EQ(vec.stride(), stride);

  EXPECT_EQ(vec.sizes(),  std::make_tuple(len));

  EXPECT_FALSE(vec.isShrunk());

  EXPECT_EQ(vec.capacity(), capacity);
  EXPECT_EQ(vec.offset(),   offset);

  EXPECT_EQ(vec.capacity(), len * stride - (stride-1));

  for ( auto i = 0; i < len; ++i ) {
    EXPECT_EQ(vec(i), valptr0[offset + i*stride]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < len; ++i ) {
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
