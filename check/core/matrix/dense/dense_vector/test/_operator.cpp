#include "../test.hpp"

TYPED_TEST(DenseVectorTest_Size8_Stride1, Assignment) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Assignment Predo");
    VectorType vec1, vec2;

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);

    EXPECT_EQ(vec2.getLength(), 0);
    EXPECT_EQ(vec2.getNelem(),  0);
    EXPECT_EQ(vec2.getSizes(),  std::make_tuple(0));
    EXPECT_EQ(vec2.getStride(), 1);

    EXPECT_TRUE(vec2.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), 0);
    EXPECT_EQ(vec2.getOffset(),   0);

    SCOPED_TRACE("Copy Assignment");
    vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValuePtr(), vec.getValuePtr());


    SCOPED_TRACE("Move Assignment");
    vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));
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

    EXPECT_EQ(vec2.getValuePtr(), vec.getValuePtr());
  }
}



TYPED_TEST(DenseVectorTest_Size8_Stride3, Assignment) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec     = this->vec_;

  {
    SCOPED_TRACE("Assignment Predo");
    VectorType vec1, vec2;

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));
    EXPECT_EQ(vec1.getStride(), 1);

    EXPECT_TRUE(vec1.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), 0);
    EXPECT_EQ(vec1.getOffset(),   0);

    EXPECT_EQ(vec2.getLength(), 0);
    EXPECT_EQ(vec2.getNelem(),  0);
    EXPECT_EQ(vec2.getSizes(),  std::make_tuple(0));
    EXPECT_EQ(vec2.getStride(), 1);

    EXPECT_TRUE(vec2.isShrunk());

    EXPECT_EQ(vec2.getCapacity(), 0);
    EXPECT_EQ(vec2.getOffset(),   0);

    SCOPED_TRACE("Copy Assignment");
    vec1 = vec;

    EXPECT_EQ(vec1.getLength(), vec.getLength());
    EXPECT_EQ(vec1.getNelem(),  vec.getNelem());
    EXPECT_EQ(vec1.getSizes(),  vec.getSizes());
    EXPECT_EQ(vec1.getStride(), vec.getStride());

    EXPECT_EQ(vec1.isShrunk(), vec.isShrunk());

    EXPECT_EQ(vec1.getCapacity(), vec.getCapacity());
    EXPECT_EQ(vec1.getOffset(),   vec.getOffset());

    EXPECT_EQ(vec1.getValuePtr(), vec.getValuePtr());


    SCOPED_TRACE("Move Assignment");
    vec2 = std::move(vec1);

    EXPECT_EQ(vec1.getLength(), 0);
    EXPECT_EQ(vec1.getNelem(),  0);
    EXPECT_EQ(vec1.getSizes(),  std::make_tuple(0));
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

    EXPECT_EQ(vec2.getValuePtr(), vec.getValuePtr());
  }
}
