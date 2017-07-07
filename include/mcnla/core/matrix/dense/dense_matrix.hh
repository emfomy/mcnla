////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.hh
/// @brief   The definition of definition of dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_ostream_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_base.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_iterator.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix.hpp>
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
/// The dense matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseMatrix : std::false_type {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
struct IsDenseMatrix<matrix::DenseMatrix<_Val, _trans>> : std::true_type {};
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix assert.
///
#define assertDenseMatrix( Type ) \
    static_assert(traits::IsDenseMatrix<Type>::value, "'"#Type"' is not a dense matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class GeMatS<CpuTag, DenseTag, _Val, _trans>
  : public DenseMatrixBase<CpuTag, _Val, _trans>,
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseMatrix
  : public DenseMatrixBase_<CpuTag, _Val, _trans>,
#endif  // DOXYGEN_SHOULD_SKIP_THIS
    public MatrixOstreamWrapper<DenseMatrix<_Val, _trans>>,
    public IterableWrapper<DenseMatrix<_Val, _trans>,
                           DenseMatrixIterator<_Val, _trans>, DenseMatrixConstIterator<_Val, _trans>> {

  friend MatrixOstreamWrapper<DenseMatrix<_Val, _trans>>;
  friend IterableWrapper<DenseMatrix<_Val, _trans>, DenseMatrixIterator<_Val, _trans>, DenseMatrixConstIterator<_Val, _trans>>;

 public:

  using IteratorType      = DenseMatrixIterator<_Val, _trans>;
  using ConstIteratorType = DenseMatrixConstIterator<_Val, _trans>;

 private:

  using BaseType          = DenseMatrixBase<CpuTag, _Val, _trans>;

 public:

  using BaseType::DenseMatrixBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc DenseMatrixBase_::operator=
  DenseMatrix& operator=( const DenseMatrix &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

};

/// @ingroup  matrix_dense_module
/// @see  DenseMatrix
template <typename _Val>
using DenseMatrixColMajor = DenseMatrix<_Val, Trans::NORMAL>;

/// @ingroup  matrix_dense_module
/// @see  DenseMatrix
template <typename _Val>
using DenseMatrixRowMajor = DenseMatrix<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
