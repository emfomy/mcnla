////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector.hh
/// @brief   The definition of COO vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_

#include <mcnla/core/matrix/coo/def.hpp>
#include <mcnla/core/matrix/base/vector_wrapper.hpp>
#include <mcnla/core/matrix/base/sparse_ostream_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/coo/coo_vector_storage.hpp>
#include <mcnla/core/matrix/coo/coo_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector traits.
///
template <typename _Val>
struct Traits<matrix::CooVector<_Val>> {

  using ValType           = _Val;

  using RealType          = matrix::CooVector<RealValT<_Val>>;
  using ComplexType       = matrix::CooVector<ComplexValT<_Val>>;

  using VectorType        = matrix::CooVector<_Val>;

  using IteratorType      = matrix::CooVectorIterator<_Val>;
  using ConstIteratorType = matrix::CooVectorConstIterator<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector instantiation type traits.
///
template <typename _Type>
struct IsCooVector : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsCooVector
///
template <typename _Val>
struct IsCooVector<matrix::CooVector<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector assert.
///
#define assertCooVector( Type ) \
    static_assert(traits::IsCooVector<Type>::value, "'"#Type"' is not a COO vector!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) vector class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class CooVector
  : public CooVectorStorage<CpuTag, _Val>,
    public VectorWrapper<CooVector<_Val>>,
    public SparseOstreamWrapper<CooVector<_Val>>,
    public IterableWrapper<CooVector<_Val>>,
    public InvertibleWrapper<CooVector<_Val>> {

  friend VectorWrapper<CooVector<_Val>>;
  friend SparseOstreamWrapper<CooVector<_Val>>;
  friend IterableWrapper<CooVector<_Val>>;
  friend InvertibleWrapper<CooVector<_Val>>;

 public:

  using ValType           = _Val;
  using ValArrayType      = Array<_Val>;
  using IdxArrayType      = Array<index_t>;
  using SizesType         = std::tuple<index_t>;

  using RealType          = CooVector<RealValT<_Val>>;
  using ComplexType       = CooVector<ComplexValT<_Val>>;

  using VectorType        = CooVector<_Val>;

  using IteratorType      = CooVectorIterator<_Val>;
  using ConstIteratorType = CooVectorConstIterator<_Val>;

 private:

  using BaseType          = CooVectorStorage<CpuTag, _Val>;

 public:

  // Constructors
  inline CooVector() noexcept;
  inline CooVector( const index_t len, const index_t nnz = 0 ) noexcept;
  inline CooVector( const SizesType sizes, const index_t nnz = 0 ) noexcept;
  inline CooVector( const index_t len, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVector( const SizesType sizes, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVector( const index_t len, const index_t nnz,
                    const ValArrayType &val, const IdxArrayType &idx0, const index_t offset = 0 ) noexcept;
  inline CooVector( const CooVector &other ) noexcept;

  // Operators
  inline CooVector& operator=( const CooVector &other ) noexcept;

  // Copy
  inline CooVector copy() const noexcept;

  // Gets information
  inline index_t idxCapacity() const noexcept;
  inline index_t idxOffset() const noexcept;

  // Gets array
  inline       IdxArrayType& idx() noexcept;
  inline const IdxArrayType& idx() const noexcept;
  inline       index_t* idxPtr() noexcept;
  inline const index_t* idxPtr() const noexcept;

  // Gets element
  inline       ValType operator()( const index_t idx ) noexcept;
  inline const ValType operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;
  inline void resize( const index_t len, const index_t nnz = 0 ) noexcept;

 protected:

  // Gets information
  inline index_t lenImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t len ) const noexcept;

  MCNLA_CRTP_BASE(BaseType);

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_
