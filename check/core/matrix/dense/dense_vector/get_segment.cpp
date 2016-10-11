#include "test.hpp"

TYPED_TEST(DenseVectorTest_Length8_Stride1, GetSegment) {
  auto stride   = this->stride_;
  auto capacity = this->capacity_;
  auto vec      = this->vec_;
  auto valarray = this->valarray_;

  const mcnla::index_t rangebegin = 1, rangelength = 5;

  auto segment = vec.getSegment({rangebegin, rangebegin+rangelength});

  EXPECT_EQ(segment.getLength(),   rangelength);
  EXPECT_EQ(segment.getNelem(),    rangelength);
  EXPECT_EQ(segment.getSizes(),    rangelength);
  EXPECT_EQ(segment.getStride(),   stride);

  EXPECT_TRUE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rangebegin);
  EXPECT_EQ(segment.getOffset(),   rangebegin);

  EXPECT_EQ(segment.getValue(),            &(vec(rangebegin)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( mcnla::index_t i = 0; i < rangelength; ++i ) {
    EXPECT_EQ(segment(i), valarray[rangebegin+i]);
  }

  mcnla::index_t i = rangebegin;
  for ( auto value : segment ) {
    EXPECT_EQ(value, valarray[i++]);
  }
}

TYPED_TEST(DenseVectorTest_Length8_Stride3, GetSegment) {
  auto stride   = this->stride_;
  auto capacity = this->capacity_;
  auto vec      = this->vec_;
  auto valarray = this->valarray_;

  const mcnla::index_t rangebegin = 1, rangelength = 5;

  auto segment = vec.getSegment({rangebegin, rangebegin+rangelength});

  EXPECT_EQ(segment.getLength(),   rangelength);
  EXPECT_EQ(segment.getNelem(),    rangelength);
  EXPECT_EQ(segment.getSizes(),    rangelength);
  EXPECT_EQ(segment.getStride(),   stride);

  EXPECT_FALSE(segment.isShrunk());

  EXPECT_EQ(segment.getCapacity(), capacity - rangebegin * stride);
  EXPECT_EQ(segment.getOffset(),   rangebegin * stride);

  EXPECT_EQ(segment.getValue(),            &(vec(rangebegin)));
  EXPECT_EQ(&(segment.getValueValarray()), &(vec.getValueValarray()));

  for ( mcnla::index_t i = 0; i < rangelength; ++i ) {
    EXPECT_EQ(segment(i), valarray[(rangebegin+i) * stride]);
  }

  mcnla::index_t i = rangebegin * stride;
  for ( auto value : segment ) {
    EXPECT_EQ(value, valarray[i]);
    i += stride;
  }
}
