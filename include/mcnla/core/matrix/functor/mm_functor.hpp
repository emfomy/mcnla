////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/functor/mm_functor.hpp
/// @brief   The definition MM functor.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_HPP_
#define MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_HPP_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/functor/mm_functor_wrapper.hpp>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_functor_module
/// The MM functor.
///
/// @tparam  _Matrix  The type of matrix A.
/// @tparam  _transb  The transpose layout of matrix B.
/// @tparam  _transc  The transpose layout of matrix C.
///
/// @see  mcnla::la::mm
///
template <class _Matrix, Trans _transb = Trans::NORMAL, Trans _transc = Trans::NORMAL>
class MmFunctor
  : public MmFunctorWrapper<ScalarT<_Matrix>, _transb, _transc> {

 public:

  using ScalarType = ScalarT<_Matrix>;
  using AType      = _Matrix;
  using BType      = DenseMatrix<ScalarT<_Matrix>, _transb>;
  using CType      = DenseMatrix<ScalarT<_Matrix>, _transc>;

 protected:

  /// The matrix A.
  const AType &matrix_;

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @copydoc  mcnla::matrix::MmFunctorWrapper::MmFunctorWrapper
  ///
  MmFunctor(
      const AType &matrix
  ) noexcept
    : matrix_(matrix) {}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @copydoc  mcnla::matrix::MmFunctorWrapper::~MmFunctorWrapper
  ///
  ~MmFunctor() noexcept override {};

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @copydoc  mcnla::matrix::MmFunctorWrapper::operator()
  ///
  void operator()(
       const BType &b,
       CType &c,
       const ScalarType alpha = 1,
       const ScalarType beta  = 0
  ) const noexcept override {
    la::mm(matrix_, b, c, alpha, beta);
  }

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_HPP_
