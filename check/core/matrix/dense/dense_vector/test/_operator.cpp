#include "../test.hpp"

TYPED_TEST(DenseVectorTest_Size8_Stride1, Assignment) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Assignment Predo");
    VectorType vec1, vec2;

    EXPECT_EQ(vec1.length(), 0);
    EXPECT_EQ(vec1.nelem(),  0);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.offset(),   0);

    EXPECT_EQ(vec2.length(), 0);
    EXPECT_EQ(vec2.nelem(),  0);
    EXPECT_EQ(vec2.stride(), 1);

    EXPECT_TRUE(vec2.isShrunk());

    EXPECT_EQ(vec2.capacity(), 0);
    EXPECT_EQ(vec2.offset(),   0);

    SCOPED_TRACE("Copy Assignment");
    vec1 = vec;

    EXPECT_EQ(vec1.length(), vec.length());
    EXPECT_EQ(vec1.nelem(),  vec.nelem());
    EXPECT_EQ(vec1.stride(), vec.stride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.capacity(), vec.capacity());
    EXPECT_EQ(vec1.offset(),   vec.offset());

    EXPECT_EQ(vec1.valPtr(), vec.valPtr());
  }
}



TYPED_TEST(DenseVectorTest_Size8_Stride3, Assignment) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Assignment Predo");
    VectorType vec1, vec2;

    EXPECT_EQ(vec1.length(), 0);
    EXPECT_EQ(vec1.nelem(),  0);
    EXPECT_EQ(vec1.stride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.offset(),   0);

    EXPECT_EQ(vec2.length(), 0);
    EXPECT_EQ(vec2.nelem(),  0);
    EXPECT_EQ(vec2.stride(), 1);

    EXPECT_TRUE(vec2.isShrunk());

    EXPECT_EQ(vec2.capacity(), 0);
    EXPECT_EQ(vec2.offset(),   0);

    SCOPED_TRACE("Copy Assignment");
    vec1 = vec;

    EXPECT_EQ(vec1.length(), vec.length());
    EXPECT_EQ(vec1.nelem(),  vec.nelem());
    EXPECT_EQ(vec1.stride(), vec.stride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.capacity(), vec.capacity());
    EXPECT_EQ(vec1.offset(),   vec.offset());

    EXPECT_EQ(vec1.valPtr(), vec.valPtr());
  }
}
