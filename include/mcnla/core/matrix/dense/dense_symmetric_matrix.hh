////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix.hh
/// @brief   The definition of dense symmetric matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>
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
template <typename _Val, Trans _trans, Uplo _uplo> class DenseSymmetricMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseSymmetricMatrix<_Val, _trans, _uplo>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::DenseSymmetricMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::DenseSymmetricMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseSymmetricMatrix<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseSymmetricMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseSymmetricMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseSymmetricMatrix<matrix::DenseSymmetricMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix assert.
///
#define assertDenseSymmetricMatrix( Type ) \
    static_assert(traits::IsDenseSymmetricMatrix<Type>::value, "'"#Type"' is not a dense symmetric matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense symmetric matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
class DenseSymmetricMatrix
  : public DenseMatrixStorage<_Val>,
    public DenseMatrixWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>>,
    public InvertibleWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");
  static_assert(!isUnitDiag(_uplo), "Unit-diagonal symmetric matrix is not supported!");

  friend MatrixWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>>;
  friend DenseMatrixWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>>;
  friend InvertibleWrapper<DenseSymmetricMatrix<_Val, _trans, _uplo>>;

 public:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType       = _Val;
  using ValArrayType  = Array<_Val>;

  using RealType      = DenseSymmetricMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType   = DenseSymmetricMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType    = DenseVector<_Val>;
  using MatrixType    = DenseSymmetricMatrix<_Val, _trans, _uplo>;

  using TransposeType = DenseSymmetricMatrix<_Val, changeTrans(_trans), changeUplo(_uplo)>;

  using GeneralType   = DenseMatrix<_Val, _trans>;

 private:

  using BaseType      = DenseMatrixStorage<_Val>;

 public:

  // Constructors
  inline DenseSymmetricMatrix() noexcept;
  inline DenseSymmetricMatrix( const index_t size ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch,
                               const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseSymmetricMatrix( const DenseSymmetricMatrix &other ) noexcept;
  inline DenseSymmetricMatrix( DenseSymmetricMatrix &&other ) noexcept;

  // Operators
  inline DenseSymmetricMatrix& operator=( const DenseSymmetricMatrix &other ) noexcept;
  inline DenseSymmetricMatrix& operator=( DenseSymmetricMatrix &&other ) noexcept;

  // Copy
  inline DenseSymmetricMatrix copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t size ) noexcept;

  // Transpose
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Change view
  inline       GeneralType& viewGeneral() noexcept;
  inline const GeneralType& viewGeneral() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSymmetricMatrixColMajor = DenseSymmetricMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseSymmetricMatrixRowMajor = DenseSymmetricMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
