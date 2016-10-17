#include "../test.hpp"

TYPED_TEST(DenseVectorTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length = 8;

  {
    VectorType vec1;

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1(0);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1(length);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getSizes(),  length);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length);
    EXPECT_EQ(vec1.getOffset(),   0);
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length   = this->length_;
  const auto stride   = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec      = this->vec_;

  {
    VectorType vec1(length, stride);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getSizes(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1(length, stride, memsize);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getSizes(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), memsize);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValue(),            vec.getValue());
    EXPECT_EQ(&(vec1.getValueValarray()), &(vec.getValueValarray()));


    VectorType vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);


    EXPECT_EQ(vec2.getLength(), vec.getLength());
    EXPECT_EQ(vec2.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec2.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec2.getStride(), vec.getStride());

    EXPECT_EQ(vec2.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec2.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec2.getValue(),            vec.getValue());
    EXPECT_EQ(&(vec2.getValueValarray()), &(vec.getValueValarray()));
  }
}


TYPED_TEST(DenseVectorTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto length   = this->length_;
  const auto stride   = this->stride_;
  const auto memsize = this->memsize_;
  const auto vec      = this->vec_;

  {
    VectorType vec1(length, stride);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getSizes(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), length * stride);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1(length, stride, memsize);

    EXPECT_EQ(vec1.getLength(), length);
    EXPECT_EQ(vec1.getNelem(),  length);
    EXPECT_EQ(vec1.getSizes(),  length);
    EXPECT_EQ(vec1.getStride(), stride);

    EXPECT_FALSE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), memsize);
    EXPECT_EQ(vec1.getOffset(),   0);
  }

  {
    VectorType vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValue(),            vec.getValue());
    EXPECT_EQ(&(vec1.getValueValarray()), &(vec.getValueValarray()));


    VectorType vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  0);
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);


    EXPECT_EQ(vec2.getLength(), vec.getLength());
    EXPECT_EQ(vec2.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec2.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec2.getStride(), vec.getStride());

    EXPECT_EQ(vec2.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec2.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec2.getValue(),            vec.getValue());
    EXPECT_EQ(&(vec2.getValueValarray()), &(vec.getValueValarray()));
  }
}
