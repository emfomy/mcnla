////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix.hh
/// @brief   The definition of dense triangular matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_ostream_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix_base.hpp>
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
/// The dense triangular matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseTriangularMatrix<_Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseTriangularMatrix<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseTriangularMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularMatrix<matrix::DenseTriangularMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularMatrix( Type ) \
    static_assert(traits::IsDenseTriangularMatrix<Type>::value, "'"#Type"' is not a dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class TrMatS<CpuTag, DenseTag, _Val, _trans, _uplo>
  : public DenseTriangularMatrixBase<CpuTag, _Val, _trans, _uplo>,
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseTriangularMatrix
  : public DenseTriangularMatrixBase_<CpuTag, _Val, _trans, _uplo>,
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    public MatrixOstreamWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>> {

  friend MatrixOstreamWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>>;

 private:

  using BaseType = DenseTriangularMatrixBase<CpuTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseTriangularMatrixBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseTriangularMatrixBase_::operator=
  DenseTriangularMatrix& operator=( const DenseTriangularMatrix &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixColMajor = DenseTriangularMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularMatrixRowMajor = DenseTriangularMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
