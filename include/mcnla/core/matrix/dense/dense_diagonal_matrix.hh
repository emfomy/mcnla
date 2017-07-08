////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.hh
/// @brief   The definition of dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_ostream_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalMatrix : std::false_type {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
struct IsDenseDiagonalMatrix<matrix::DenseDiagonalMatrix<_Val>> : std::true_type {};
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix assert.
///
#define assertDenseDiagonalMatrix( Type ) \
    static_assert(traits::IsDenseDiagonalMatrix<Type>::value, "'"#Type"' is not a dense diagonal matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DiMatS<CpuTag, DenseTag, _Val>
  : public DenseDiagonalMatrixBase<CpuTag, _Val>,
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseDiagonalMatrix
  : public DenseDiagonalMatrixBase_<CpuTag, _Val>,
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    public MatrixOstreamWrapper<DenseDiagonalMatrix<_Val>> {

  friend MatrixOstreamWrapper<DenseDiagonalMatrix<_Val>>;

 private:

  using BaseType = DenseDiagonalMatrixBase<CpuTag, _Val>;

 public:

  using BaseType::DenseDiagonalMatrixBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseDiagonalMatrixBase_::operator=
  DenseDiagonalMatrix& operator=( const DenseDiagonalMatrix &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
