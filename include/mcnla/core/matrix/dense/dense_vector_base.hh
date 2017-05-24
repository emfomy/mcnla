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

#ifdef DOXYGEN_SHOULD_SKIP_THIS
template <class _Core, typename _Val>
using DenseVectorBase = DenseVectorBase_<_Core, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector base class.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Core, typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DenseVectorBase
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseVectorBase_
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseVectorStorage<_Core, _Val>,
    public DenseVectorWrapper<GeVecS<_Core, DenseTag, _Val>>,
    public InvertibleWrapper<GeVecS<_Core, DenseTag, _Val>> {

 private:

  using DerivedType = GeVecS<_Core, DenseTag, _Val>;

  friend VectorWrapper<DerivedType>;
  friend DenseVectorWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  using ValType      = _Val;
  using ValArrayType = ArrS<_Core, _Val>;
  using SizesType    = std::tuple<index_t>;

  using VectorType   = GeVecS<_Core, DenseTag, _Val>;

  using DiagonalType = DiMatS<_Core, DenseTag, _Val>;

 private:

  using BaseType     = DenseVectorStorage<_Core, _Val>;

 public:

  // Constructors
  inline DenseVectorBase() noexcept;
  inline DenseVectorBase( const index_t len, const index_t stride = 1 ) noexcept;
  inline DenseVectorBase( const SizesType sizes, const index_t stride = 1 ) noexcept;
  inline DenseVectorBase( const index_t len, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorBase( const SizesType sizes, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorBase( const index_t len, const index_t stride,
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
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;
  inline void resize( const index_t len ) noexcept;

  // Changes view
  inline       DiagonalType& viewDiagonal() noexcept;
  inline const DiagonalType& viewDiagonal() const noexcept;

  // Gets segment
  inline       VectorType operator()( const IdxRange &range ) noexcept;
  inline const VectorType operator()( const IdxRange &range ) const noexcept;

 protected:

  // Gets information
  inline index_t lenImpl() const noexcept;
  inline index_t mlenImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t len ) const noexcept;

  MCNLA_CRTP_BASE(BaseType);
  MCNLA_CRTP_DERIVED(DerivedType);

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_BASE_HH_