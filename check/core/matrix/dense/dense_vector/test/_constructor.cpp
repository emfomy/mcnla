#include "../test.hpp"

TYPED_TEST(DenseVectorTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto len    = 8;
  const auto sizes  = std::make_tuple(len);

  {
    SCOPED_TRACE("Constructor()");
    VectorType vec1;

    EXPECT_EQ(vec1.len(),    0);
    EXPECT_EQ(vec1.nelem(),  0);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(0)");
    VectorType vec1(0);

    EXPECT_EQ(vec1.len(),    0);
    EXPECT_EQ(vec1.nelem(),  0);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(0, 1)");
    VectorType vec1(0, 1);

    EXPECT_EQ(vec1.len(),    0);
    EXPECT_EQ(vec1.nelem(),  0);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(len)");
    VectorType vec1(len);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), len);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor({len})");
    VectorType vec1(sizes);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), len);
    EXPECT_EQ(vec1.offset(),   0);
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto len     = this->len_;
  const auto stride  = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec     = this->vec_;
  const auto sizes   = std::make_tuple(len);

  {
    SCOPED_TRACE("Constructor(len, stride)");
    VectorType vec1(len, stride);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), len);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor({len}, stride)");
    VectorType vec1(sizes, stride);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), len);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(len, stride, memsize)");
    VectorType vec1(len, stride, memsize);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), memsize);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor({len}, stride, memsize)");
    VectorType vec1(sizes, stride, memsize);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), memsize);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Copy Constructor");
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.len(),    vec.len());
    EXPECT_EQ(vec1.nelem(),  vec.nelem());
    EXPECT_EQ(vec1.stride(), vec.stride());

    EXPECT_EQ(vec1.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec1.capacity(), vec.capacity());
    EXPECT_EQ(vec1.offset(),   vec.offset());

    EXPECT_EQ(vec1.valPtr(), vec.valPtr());
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto len     = this->len_;
  const auto stride  = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Constructor(len, stride)");
    VectorType vec1(len, stride);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), len * stride);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(len, stride, memsize)");
    VectorType vec1(len, stride, memsize);

    EXPECT_EQ(vec1.len(),    len);
    EXPECT_EQ(vec1.nelem(),  len);
    EXPECT_EQ(vec1.stride(), stride);

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), memsize);
    EXPECT_EQ(vec1.offset(),   0);
  }

  {
    SCOPED_TRACE("Copy Constructor");
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.len(),    vec.len());
    EXPECT_EQ(vec1.nelem(),  vec.nelem());
    EXPECT_EQ(vec1.stride(), vec.stride());

    EXPECT_EQ(vec1.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec1.capacity(), vec.capacity());
    EXPECT_EQ(vec1.offset(),   vec.offset());

    EXPECT_EQ(vec1.valPtr(), vec.valPtr());
  }
}
