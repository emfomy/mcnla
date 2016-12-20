#include "../test.hpp"

TYPED_TEST(DenseVectorTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length = 8;

  {
    SCOPED_TRACE("Constructor()");
    VectorType vec1;

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(0)");
    VectorType vec1(0);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(0, 1)");
    VectorType vec1(0, 1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(length)");
    VectorType vec1(length);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(length));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length);
    EXPECT_EQ(vec1.getOffset(),   0);
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length  = this->length_;
  const auto stride  = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Constructor(length, stride)");
    VectorType vec1(length, stride);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(length));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(length, stride, memsize)");
    VectorType vec1(length, stride, memsize);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(length));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), memsize);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Copy Constructor");
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());

    EXPECT_EQ(vec1.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValuePtr(), vec.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    VectorType vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);


    EXPECT_EQ(vec2.getLength(), vec.getLength());
    EXPECT_EQ(vec2.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec2.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec2.getStride(), vec.getStride());

    EXPECT_EQ(vec2.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec2.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec2.getValuePtr(), vec.getValuePtr());
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length  = this->length_;
  const auto stride  = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Constructor(length, stride)");
    VectorType vec1(length, stride);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(length));

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length * stride);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Constructor(length, stride, memsize)");
    VectorType vec1(length, stride, memsize);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(length));

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), memsize);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    SCOPED_TRACE("Copy Constructor");
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());

    EXPECT_EQ(vec1.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValuePtr(), vec.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    VectorType vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);


    EXPECT_EQ(vec2.getLength(), vec.getLength());
    EXPECT_EQ(vec2.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec2.getStride(), vec.getStride());

    EXPECT_EQ(vec2.getSizes(),  vec.getSizes());

    EXPECT_EQ(vec2.isShrunk(),  vec.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec2.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec2.getValuePtr(), vec.getValuePtr());
  }
}
