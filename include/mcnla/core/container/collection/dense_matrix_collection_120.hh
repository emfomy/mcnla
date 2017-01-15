////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/collection/dense_matrix_collection_120.hh
/// @brief   The definition of dense matrix collection with dimension order [1 2 0].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_COLLECTION_DENSE_MATRIX_COLLECTION_120_HH_
#define MCNLA_CORE_CONTAINER_COLLECTION_DENSE_MATRIX_COLLECTION_120_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <tuple>
#include <mcnla/core/container/collection/matrix_collection_wrapper.hpp>
#include <mcnla/core/container/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseMatrixCollection120;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace container

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits of dense matrix collection with dimension order [1 2 0].
///
template <typename _Scalar>
struct Traits<container::DenseMatrixCollection120<_Scalar>> {

  using ScalarType = _Scalar;
  using RealType    = container::DenseMatrixCollection120<RealScalarT<_Scalar>>;
  using ComplexType = container::DenseMatrixCollection120<ComplexScalarT<_Scalar>>;
  using SetType     = container::DenseMatrixCollection120<_Scalar>;
  using MatrixType  = container::DenseMatrixRowMajor<_Scalar>;

};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_collection_module
/// The dense matrix collection with dimension order [1 2 0].
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseMatrixCollection120
  : public MatrixCollectionWrapper<DenseMatrixCollection120<_Scalar>> {

  friend MatrixCollectionWrapper<DenseMatrixCollection120<_Scalar>>;

 public:

  using ScalarType = _Scalar;
  using SetType    = DenseMatrixCollection120<_Scalar>;
  using MatrixType = DenseMatrixRowMajor<_Scalar>;

 private:

  using BaseType = MatrixCollectionWrapper<DenseMatrixCollection120<_Scalar>>;

 protected:

  /// The base data.
  MatrixType data_;

  /// The number of columns in each matrix.
  index_t ncol_;

 public:

  // Constructors
  inline DenseMatrixCollection120() noexcept;
  inline DenseMatrixCollection120( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline DenseMatrixCollection120( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  inline DenseMatrixCollection120( const index_t ncol, const MatrixType &data ) noexcept;
  inline DenseMatrixCollection120( const DenseMatrixCollection120 &other ) noexcept;
  inline DenseMatrixCollection120( DenseMatrixCollection120 &&other ) noexcept;

  // Operators
  inline DenseMatrixCollection120& operator=( const DenseMatrixCollection120 &other ) noexcept;
  inline DenseMatrixCollection120& operator=( DenseMatrixCollection120 &&other ) noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;

  // Gets data
  inline       MatrixType& data() noexcept;
  inline const MatrixType& data() const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Gets collection
  using BaseType::operator();
  inline       SetType operator()( const IdxRange &idxrange ) noexcept;
  inline const SetType operator()( const IdxRange &idxrange ) const noexcept;
  inline       SetType operator()( const char*, const char*, const IdxRange &idxrange ) noexcept;
  inline const SetType operator()( const char*, const char*, const IdxRange &idxrange ) const noexcept;
  inline       SetType operator()( const IdxRange &rowrange, const char*, const char* ) noexcept;
  inline const SetType operator()( const IdxRange &rowrange, const char*, const char* ) const noexcept;

  // Gets matrix
  inline       MatrixType unfold() noexcept;
  inline const MatrixType unfold() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t nmatImpl() const noexcept;

  // Gets matrix
  inline       MatrixType getMatrixImpl( const index_t idx ) noexcept;
  inline const MatrixType getMatrixImpl( const index_t idx ) const noexcept;

};

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_COLLECTION_DENSE_MATRIX_COLLECTION_120_HH_
