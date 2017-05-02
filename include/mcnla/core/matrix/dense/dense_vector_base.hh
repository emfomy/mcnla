////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_base.hh
/// @brief   The definition of dense vector base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_

#include <mcnla/core/matrix/def.hpp>
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
/// @tparam  _Val       The value type.
/// @tparam  _Vector    The vector template.
/// @tparam  _Diagonal  The diagonal matrix template.
/// @tparam  _Array     The array template.
///
template <typename _Val,
          template <typename> class _Vector,
          template <typename> class _Diagonal,
          template <typename> class _Array>
class DenseVectorBase
  : public DenseVectorStorage<_Val, _Array>,
    public VectorWrapper<_Vector<_Val>>,
    public InvertibleWrapper<_Vector<_Val>> {

  friend VectorWrapper<_Vector<_Val>>;
  friend InvertibleWrapper<_Vector<_Val>>;

 public:

  using DerivedType  = _Vector<_Val>;

  using ValType      = _Val;
  using ValArrayType = _Array<_Val>;
  using SizesType    = std::tuple<index_t>;

  using RealType     = RealT<DerivedType>;
  using ComplexType  = ComplexT<DerivedType>;

  using VectorType   = _Vector<_Val>;

  using DiagonalType = _Diagonal<_Val>;

 private:

  using BaseType     = DenseVectorStorage<ValType>;

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
