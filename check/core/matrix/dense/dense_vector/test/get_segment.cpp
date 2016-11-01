#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseVectorTest_Size8_Stride1, GetSegment) {
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valarray = this->valarray_;

  const mcnla::index_t idx0 = 2, idxs = 5;

  auto segment = vec.getSegment({idx0, idx0+idxs});

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), stride);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx0);
  EXPECT_EQ(segment.getOffset(),   offset + idx0);

  EXPECT_EQ(segment.getValue(),            &(vec(idx0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), vec(i+idx0));
  }

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx0)]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < idxs; ++i ) {
    tmp.push(valarray[offset + (i+idx0)]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseVectorTest_Size8_Stride3, GetSegment) {
  const auto stride   = this->stride_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto valarray = this->valarray_;

  const mcnla::index_t idx0 = 2, idxs = 5;

  auto segment = vec.getSegment({idx0, idx0+idxs});

  EXPECT_EQ(segment.getLength(), idxs);
  EXPECT_EQ(segment.getNelem(),  idxs);
  EXPECT_EQ(segment.getSizes(),  idxs);
  EXPECT_EQ(segment.getStride(), stride);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx0 * stride);
  EXPECT_EQ(segment.getOffset(),   offset + idx0 * stride);

  EXPECT_EQ(segment.getValue(),            &(vec(idx0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), vec(i+idx0));
  }

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), valarray[offset + (i+idx0)*stride]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < idxs; ++i ) {
    tmp.push(valarray[offset + (i+idx0)*stride]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}