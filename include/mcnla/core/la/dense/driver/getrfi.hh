////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/getrfi.hh
/// @brief   The definition of LAPACK GETRF+GETRI driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_DRIVER_HH_
#define MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_DRIVER_HH_

#include <mcnla/core/la/def.hpp>
#include <tuple>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_le_module
/// @brief  The LU-inverse driver of general square matrices.
///
/// @see  mcnla::la::getrf, mcnla::la::getri
///
template <class _Matrix>
class GetrfiDriver {

  assertDenseMatrix(_Matrix);

 private:

  static constexpr Trans trans = _Matrix::trans;

  using ValType       = ValT<_Matrix>;
  using MatrixType    = _Matrix;
  using VectorType    = VectorT<_Matrix>;
  using IdxVectorType = DenseVector<index_t>;

 protected:

  /// The matrix size.
  index_t size_;

  /// The workspace.
  IdxVectorType ipiv_;

  /// The workspace.
  VectorType work_;

 public:

  // Constructors
  inline GetrfiDriver() noexcept;
  inline GetrfiDriver( const index_t size ) noexcept;
  inline GetrfiDriver( const MatrixType &a ) noexcept;

  // Operators
  inline void operator()( MatrixType &a ) noexcept;
  inline void operator()( MatrixType &&a ) noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t> sizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;

 protected:

  // Computes
  inline void compute( MatrixType &a ) noexcept;

  // Queries
  inline index_t query( const index_t size ) noexcept;

};

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_DRIVER_HH_
