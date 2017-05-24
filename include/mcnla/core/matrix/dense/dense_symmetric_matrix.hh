////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix.hh
/// @brief   The definition of dense symmetric matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_ostream_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseSymmetricMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseSymmetricMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseSymmetricMatrix<matrix::DenseSymmetricMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix assert.
///
#define assertDenseSymmetricMatrix( Type ) \
    static_assert(traits::IsDenseSymmetricMatrix<Type>::value, "'"#Type"' is not a dense symmetric matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense symmetric matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class SyMatS<CpuTag, DenseTag, _Val, _trans, _uplo>
  : public DenseSymmetricMatrixBase<CpuTag, _Val, _trans, _uplo>,
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseSymmetricMatrix
  : public DenseSymmetricMatrixBase_<CpuTag, _Val, _trans, _uplo>,
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    public MatrixOstreamWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>> {

  friend MatrixOstreamWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>>;

 private:

  using BaseType = DenseSymmetricMatrixBase<CpuTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseSymmetricMatrixBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseSymmetricMatrixBase_::operator=
  DenseSymmetricMatrix& operator=( const DenseSymmetricMatrix &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSymmetricMatrixColMajor = DenseSymmetricMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseSymmetricMatrixRowMajor = DenseSymmetricMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
