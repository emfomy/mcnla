////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/vector_set_base.ipp
/// @brief   The implementation of vector set interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_VECTOR_SET_IPP_
#define MCNLA_CORE_MATRIX_SET_VECTOR_SET_IPP_

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
VectorSet<_Derived>::VectorSet() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of vector.
///
template <class _Derived>
index_t VectorSet<_Derived>::getLength() const noexcept { return this->derived().getLength(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of vectors.
///
template <class _Derived>
index_t VectorSet<_Derived>::getNvec() const noexcept { return this->derived().getNvec(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector.
///
template <class _Derived>
typename VectorSet<_Derived>::VectorType VectorSet<_Derived>::getVector( const index_t idx ) noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
const typename VectorSet<_Derived>::VectorType VectorSet<_Derived>::getVector( const index_t idx ) const noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
typename VectorSet<_Derived>::VectorType VectorSet<_Derived>::operator()( const index_t idx ) noexcept {
  return this->derived().getVector(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVector
///
template <class _Derived>
const typename VectorSet<_Derived>::VectorType VectorSet<_Derived>::operator()( const index_t idx ) const noexcept {
  return this->derived().getVector(idx);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_VECTOR_SET_IPP_
