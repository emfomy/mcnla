////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/lacpy.hpp
/// @brief   The BLAS LACPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_LACPY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_LACPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/lacpy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

//@{

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpyImpl(
    const DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
          DenseSymmetricMatrix<_Val, _trans, _uplo> &b
) noexcept {
  static_assert(!isUnitDiag(_uplo), "LACPY for unit-diagonal matrices is not implemented!");
  mcnla_assert_eq(a.sizes(), b.sizes());
  detail::lacpy(toUploChar(_uplo, _trans), a.dim0(), a.dim1(), a.valPtr(), a.pitch(), b.valPtr(), b.pitch());
}

template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpyImpl(
    const DenseTriangularMatrix<_Val, _trans, _uplo> &a,
          DenseTriangularMatrix<_Val, _trans, _uplo> &b
) noexcept {
  static_assert(!isUnitDiag(_uplo), "LACPY for unit-diagonal matrices is not implemented!");
  mcnla_assert_eq(a.sizes(), b.sizes());
  detail::lacpy(toUploChar(_uplo, _trans), a.dim0(), a.dim1(), a.valPtr(), a.pitch(), b.valPtr(), b.pitch());
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_aux_module
/// @brief  Copies a symmetric matrix to another symmetric matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpy(
    const DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
          DenseSymmetricMatrix<_Val, _trans, _uplo> &b
) noexcept {
  detail::lacpyImpl(a, b);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpy(
    const DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
          DenseSymmetricMatrix<_Val, _trans, _uplo> &&b
) noexcept {
  detail::lacpyImpl(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_aux_module
/// @brief  Copies a triangular matrix to another triangular matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpy(
    const DenseTriangularMatrix<_Val, _trans, _uplo> &a,
          DenseTriangularMatrix<_Val, _trans, _uplo> &b
) noexcept {
  detail::lacpyImpl(a, b);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans, Uplo _uplo>
inline void lacpy(
    const DenseTriangularMatrix<_Val, _trans, _uplo> &a,
          DenseTriangularMatrix<_Val, _trans, _uplo> &&b
) noexcept {
  detail::lacpyImpl(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Copies a symmetric matrix to another symmetric matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo>
inline void copy(
    const DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
          DenseSymmetricMatrix<_Val, _trans, _uplo> &b
) noexcept {
  lacpy(a, b);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans, Uplo _uplo>
inline void copy(
    const DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
          DenseSymmetricMatrix<_Val, _trans, _uplo> &&b
) noexcept {
  lacpy(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Copies a triangular matrix to another triangular matrix.
///
template <typename _Val, Trans _trans, Uplo _uplo>
inline void copy(
    const DenseTriangularMatrix<_Val, _trans, _uplo> &a,
          DenseTriangularMatrix<_Val, _trans, _uplo> &b
) noexcept {
  lacpy(a, b);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans, Uplo _uplo>
inline void copy(
    const DenseTriangularMatrix<_Val, _trans, _uplo> &a,
          DenseTriangularMatrix<_Val, _trans, _uplo> &&b
) noexcept {
  lacpy(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_LACPY_HPP_
