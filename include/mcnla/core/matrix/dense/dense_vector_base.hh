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
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Core, typename _Val>
class DenseVectorBase
  : public DenseVectorStorage<_Core, _Val>,
    public VectorWrapper<GeVecI<_Core, DenseTag, _Val>>,
    public InvertibleWrapper<GeVecI<_Core, DenseTag, _Val>> {

 private:

  using DerivedType = GeVecI<_Core, DenseTag, _Val>;

  friend VectorWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  using ValType      = _Val;
  using ValArrayType = ArrI<_Core, _Val>;
  using SizesType    = std::tuple<index_t>;

  using RealType     = GeVecI<_Core, DenseTag, RealValT<_Val>>;
  using ComplexType  = GeVecI<_Core, DenseTag, ComplexValT<_Val>>;

  using VectorType   = GeVecI<_Core, DenseTag, _Val>;

  using DiagonalType = DiMatI<_Core, DenseTag, _Val>;

 private:

  using BaseType     = DenseVectorStorage<_Core, _Val>;

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_BASE(BaseType);
  CRTP_DERIVED(DerivedType);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_
