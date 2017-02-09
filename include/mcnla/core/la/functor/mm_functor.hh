////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/functor/mm_functor.hh
/// @brief   The definition MM functor.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HH_
#define MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HH_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/la/functor/mm_functor_wrapper.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The la namespace.
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_functor_module
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

  MmFunctor( const AType &matrix ) noexcept;

  ~MmFunctor() noexcept override;

  virtual void operator()( const BType &b, CType &c,
                           const ScalarType alpha = 1, const ScalarType beta  = 0 ) const noexcept override;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HH_
