////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/functor/mm_functor_wrapper.hpp
/// @brief   The MM functor wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_
#define MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>

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
/// The MM functor wrapper.
///
/// @tparam  _Val     The value type.
/// @tparam  _transb  The transpose storage layout of matrix B.
/// @tparam  _transc  The transpose storage layout of matrix C.
///
/// @see  mcnla::la::mm
///
template <class _Val, Trans _transb = Trans::NORMAL, Trans _transc = Trans::NORMAL>
class MmFunctorWrapper {

 protected:

  using BType = DenseMatrix<_Val, _transb>;
  using CType = DenseMatrix<_Val, _transc>;

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
  virtual void operator()( const BType &b, CType &c, const _Val alpha = 1, const _Val beta = 0 ) const noexcept = 0;

  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  inline void operator()( const BType &b, CType &&c, const _Val alpha = 1, const _Val beta = 0 ) const noexcept {
    (*this)(b, c, alpha, beta);
  }
  #endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_WRAPPER_HPP_
