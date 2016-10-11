#include "test.hpp"
#include <queue>

TYPED_TEST(DenseVectorSize_Length8_Stride1, GetSegment) {
  auto stride   = this->stride_;
  auto capacity = this->capacity_;
  auto vec      = this->vec_;
  auto valarray = this->valarray_;

  const mcnla::index_t idx0 = 2, idxs = 5;

  auto segment = vec.getSegment({idx0, idx0+idxs});

  EXPECT_EQ(segment.getLength(),   idxs);
  EXPECT_EQ(segment.getNelem(),    idxs);
  EXPECT_EQ(segment.getSizes(),    idxs);
  EXPECT_EQ(segment.getStride(),   stride);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx0);
  EXPECT_EQ(segment.getOffset(),   idx0);

  EXPECT_EQ(segment.getValue(),            &(vec(idx0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), vec(i+idx0));
  }

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), valarray[i+idx0]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < idxs; ++i ) {
    tmp.push(valarray[i+idx0]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}


TYPED_TEST(DenseVectorSize_Length8_Stride3, GetSegment) {
  auto stride   = this->stride_;
  auto capacity = this->capacity_;
  auto vec      = this->vec_;
  auto valarray = this->valarray_;

  const mcnla::index_t idx0 = 1, idxs = 5;

  auto segment = vec.getSegment({idx0, idx0+idxs});

  EXPECT_EQ(segment.getLength(),   idxs);
  EXPECT_EQ(segment.getNelem(),    idxs);
  EXPECT_EQ(segment.getSizes(),    idxs);
  EXPECT_EQ(segment.getStride(),   stride);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - idx0 * stride);
  EXPECT_EQ(segment.getOffset(),   idx0 * stride);

  EXPECT_EQ(segment.getValue(),            &(vec(idx0)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), vec(i+idx0));
  }

  for ( auto i = 0; i < idxs; ++i ) {
    EXPECT_EQ(segment(i), valarray[(i+idx0) * stride]);
  }

  std::queue<TypeParam> tmp;
  for ( auto i = 0; i < idxs; ++i ) {
    tmp.push(valarray[(i+idx0) * stride]);
  }
  for ( auto value : segment ) {
    EXPECT_EQ(value, tmp.front());
    tmp.pop();
  }
  EXPECT_EQ(tmp.size(), 0);
}
