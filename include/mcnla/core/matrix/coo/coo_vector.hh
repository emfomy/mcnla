////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector.hh
/// @brief   The definition of COO vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/base/vector_wrapper.hpp>
#include <mcnla/core/matrix/coo/coo_vector_storage.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector traits.
///
template <typename _Scalar>
struct Traits<matrix::CooVector<_Scalar>> {
  static constexpr index_t ndim = 1;

  using ScalarType  = _Scalar;

  using RealType    = matrix::CooVector<RealScalarT<_Scalar>>;
  using ComplexType = matrix::CooVector<ComplexScalarT<_Scalar>>;

  using VectorType  = matrix::CooVector<_Scalar>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class CooVector
  : public CooVectorStorage<_Scalar>,
    public VectorWrapper<CooVector<_Scalar>>,
    public InvertibleWrapper<CooVector<_Scalar>> {

  friend VectorWrapper<CooVector<_Scalar>>;
  friend InvertibleWrapper<CooVector<_Scalar>>;

 public:

  static constexpr index_t ndim = 1;

  using ScalarType   = _Scalar;
  using ValArrayType = Array<_Scalar>;
  using IdxArrayType = Array<index_t>;
  using SizesType    = std::tuple<index_t>;

  using RealType     = CooVector<RealScalarT<_Scalar>>;
  using ComplexType  = CooVector<ComplexScalarT<_Scalar>>;

  using VectorType   = CooVector<_Scalar>;

 private:

  using BaseType     = CooVectorStorage<_Scalar>;

 public:

  // Constructors
  inline CooVector() noexcept;
  inline CooVector( const index_t length, const index_t nnz = 0 ) noexcept;
  inline CooVector( const SizesType sizes, const index_t nnz = 0 ) noexcept;
  inline CooVector( const index_t length, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVector( const SizesType sizes, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVector( const index_t length, const index_t nnz,
                    const ValArrayType &val, const IdxArrayType &idx0, const index_t offset = 0 ) noexcept;
  inline CooVector( const CooVector &other ) noexcept;
  inline CooVector( CooVector &&other ) noexcept;

  // Operators
  inline CooVector& operator=( const CooVector &other ) noexcept;
  inline CooVector& operator=( CooVector &&other ) noexcept;

  // Gets information
  inline index_t nidx() const noexcept;

  // Gets element
  inline       ScalarType& operator()( const index_t idx ) noexcept;
  inline const ScalarType& operator()( const index_t idx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t idx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t length, const index_t nnz = 0 ) noexcept;

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

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_HH_
