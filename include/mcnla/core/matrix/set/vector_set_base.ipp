////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/vector_set_base.ipp
/// @brief   The implementation of vector set interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_IPP_
#define MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_IPP_

#include <mcnla/core/matrix/set/vector_set_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
VectorSetBase<_Derived>::VectorSetBase() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of vector.
///
template <class _Derived>
index_t VectorSetBase<_Derived>::getLength() const noexcept { return this->derived().getLength(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of vectors.
///
template <class _Derived>
index_t VectorSetBase<_Derived>::getNvec() const noexcept { return this->derived().getNvec(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector.
///
template <class _Derived>
typename VectorSetBase<_Derived>::VectorType VectorSetBase<_Derived>::getVector( const index_t idx ) noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
const typename VectorSetBase<_Derived>::VectorType VectorSetBase<_Derived>::getVector( const index_t idx ) const noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
typename VectorSetBase<_Derived>::VectorType VectorSetBase<_Derived>::operator()( const index_t idx ) noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
const typename VectorSetBase<_Derived>::VectorType VectorSetBase<_Derived>::operator()( const index_t idx ) const noexcept {
  return this->derived().getVector(idx);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_IPP_
