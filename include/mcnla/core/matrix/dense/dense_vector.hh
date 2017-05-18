////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.hh
/// @brief   The definition of dense vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/dense_vector_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector_iterator.hpp>
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
/// The dense vector traits.
///
template <typename _Val>
struct Traits<matrix::GeVecI<CoreTag, DenseTag, _Val>> {

  using ValType           = _Val;

  using RealType          = matrix::GeVecI<CoreTag, DenseTag, RealValT<_Val>>;
  using ComplexType       = matrix::GeVecI<CoreTag, DenseTag, ComplexValT<_Val>>;

  using VectorType        = matrix::GeVecI<CoreTag, DenseTag, _Val>;

  using IteratorType      = matrix::DenseVectorIterator<_Val>;
  using ConstIteratorType = matrix::DenseVectorConstIterator<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector instantiation type traits.
///
template <typename _Type>
struct IsDenseVector : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseVector
///
template <typename _Val>
struct IsDenseVector<matrix::GeVecI<CoreTag, DenseTag, _Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector assert.
///
#define assertDenseVector( Type ) \
    static_assert(traits::IsDenseVector<Type>::value, "'"#Type"' is not a dense vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class GeVecI<CoreTag, DenseTag, _Val>
  : public DenseVectorBase<CoreTag, _Val>,
    public DenseVectorWrapper<GeVecI<CoreTag, DenseTag, _Val>>,
    public IterableWrapper<GeVecI<CoreTag, DenseTag, _Val>> {

  friend DenseVectorWrapper<GeVecI<CoreTag, DenseTag, _Val>>;
  friend IterableWrapper<GeVecI<CoreTag, DenseTag, _Val>>;

 private:

  using IteratorType      = DenseVectorIterator<_Val>;
  using ConstIteratorType = DenseVectorConstIterator<_Val>;

  using BaseType          = DenseVectorBase<CoreTag, _Val>;

 public:

  using BaseType::DenseVectorBase;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Val>
using DenseVector = GeVecI<CoreTag, DenseTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_
