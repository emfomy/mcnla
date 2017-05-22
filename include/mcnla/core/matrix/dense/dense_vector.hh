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
struct Traits<matrix::DenseVector<_Val>> {

  using ValType           = _Val;

  using RealType          = matrix::DenseVector<RealValT<_Val>>;
  using ComplexType       = matrix::DenseVector<ComplexValT<_Val>>;

  using VectorType        = matrix::DenseVector<_Val>;

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
struct IsDenseVector<matrix::DenseVector<_Val>> : std::true_type {};

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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class GeVecS<CpuTag, DenseTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseVector
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseVectorBase<CpuTag, _Val>,
    public DenseVectorWrapper<DenseVector<_Val>>,
    public IterableWrapper<DenseVector<_Val>> {

  friend DenseVectorWrapper<DenseVector<_Val>>;
  friend IterableWrapper<DenseVector<_Val>>;

 private:

  using IteratorType      = DenseVectorIterator<_Val>;
  using ConstIteratorType = DenseVectorConstIterator<_Val>;

  using BaseType          = DenseVectorBase<CpuTag, _Val>;

 public:

  using BaseType::DenseVectorBase;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HH_
