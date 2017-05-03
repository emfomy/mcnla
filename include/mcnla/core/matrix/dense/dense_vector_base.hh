////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_base.hh
/// @brief   The definition of dense vector base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/vector_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector base class.
///
/// @tparam  _Val    The value type.
/// @tparam  _Types  The type templates.
///
template <typename _Val, class _Types>
class DenseVectorBase
  : public DenseVectorStorage<_Val, _Types::template ArrayT>,
    public VectorWrapper<typename _Types::template GeVecT<_Val>>,
    public InvertibleWrapper<typename _Types::template GeVecT<_Val>> {

  friend VectorWrapper<typename _Types::template GeVecT<_Val>>;
  friend InvertibleWrapper<typename _Types::template GeVecT<_Val>>;

 public:

  using DerivedType  = typename _Types::template GeVecT<_Val>;

  using ValType      = _Val;
  using ValArrayType = typename _Types::template ArrayT<_Val>;
  using SizesType    = std::tuple<index_t>;

  using RealType     = typename _Types::template GeVecT<RealValT<_Val>>;
  using ComplexType  = typename _Types::template GeVecT<ComplexValT<_Val>>;

  using VectorType   = typename _Types::template GeVecT<_Val>;

  using DiagonalType = typename _Types::template DiMatT<_Val>;

 private:

  using BaseType     = DenseVectorStorage<_Val, _Types::template ArrayT>;

 public:

  // Constructors
  inline DenseVectorBase() noexcept;
  inline DenseVectorBase( const index_t length, const index_t stride = 1 ) noexcept;
  inline DenseVectorBase( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseVectorBase( const index_t length, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorBase( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorBase( const index_t length, const index_t stride,
                          const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseVectorBase( const DerivedType &other ) noexcept;

  // Operators
  inline DerivedType& operator=( const DerivedType &other ) noexcept;

  // Copy
  inline DerivedType copy() const noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets element
  inline       ValType& operator()( const index_t idx ) noexcept;
  inline const ValType& operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t length ) noexcept;
  inline void resize( const index_t length, const index_t stride ) noexcept;

  // Changes view
  inline       DiagonalType& viewDiagonal() noexcept;
  inline const DiagonalType& viewDiagonal() const noexcept;

  // Gets segment
  inline       VectorType operator()( const IdxRange &range ) noexcept;
  inline const VectorType operator()( const IdxRange &range ) const noexcept;

 protected:

  // Gets information
  inline index_t lengthImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t length ) const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_
