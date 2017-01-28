////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/functor/mm_functor_wrapper.hpp
/// @brief   The MM functor wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

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
/// The MM functor wrapper.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _transb  The transpose layout of matrix B.
/// @tparam  _transc  The transpose layout of matrix C.
///
/// @see  mcnla::la::mm
///
template <class _Scalar, Trans _transb = Trans::NORMAL, Trans _transc = Trans::NORMAL>
class MmFunctorWrapper {

 protected:

  using BType = DenseMatrix<_Scalar, _transb>;
  using CType = DenseMatrix<_Scalar, _transc>;

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  The default constructor.
  ///
  MmFunctorWrapper() noexcept = default;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  The default destructor.
  ///
  virtual ~MmFunctorWrapper() noexcept = default;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Apply the functor.
  ///
  virtual void operator()( const BType &b, CType &c, const _Scalar alpha = 1, const _Scalar beta = 0 ) const noexcept = 0;

  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  inline void operator()( const BType &b, CType &&c, const _Scalar alpha = 1, const _Scalar beta = 0 ) const noexcept {
    (*this)(b, c, alpha, beta);
  }
  #endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_
