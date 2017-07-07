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
/// @note  This driver runs GETRF and GETRI.
///
template <typename _Val, Trans _trans>
class DenseGetrfiDriver {

 private:

  using ValType       = _Val;
  using MatrixType    = DenseMatrix<_Val, _trans>;
  using VectorType    = DenseVector<_Val>;
  using IdxVectorType = DenseVector<index_t>;

 protected:

  /// The matrix size.
  index_t size_;

  /// The pivot indices.
  IdxVectorType ipiv_;

  /// The workspace.
  VectorType work_;

 public:

  // Constructors
  inline DenseGetrfiDriver() noexcept;
  inline DenseGetrfiDriver( const index_t size ) noexcept;
  inline DenseGetrfiDriver( const MatrixType &a ) noexcept;

  // Operators
  inline void operator()( MatrixType &a ) noexcept;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  inline void operator()( MatrixType &&a ) noexcept;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t, index_t> sizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;

 protected:

  // Computes
  inline void compute( MatrixType &a ) noexcept;

  // Queries workspace size
  inline index_t query() noexcept;

};

/// @ingroup  la_dense_lapack_ls_module
/// @see  DenseGetrfiDriver
template <typename _Val>
using DenseGetrfiDriverColMajor = DenseGetrfiDriver<_Val, Trans::NORMAL>;

/// @ingroup  la_dense_lapack_ls_module
template <typename _Val>
/// @see  DenseGetrfiDriver
using DenseGetrfiDriverRowMajor = DenseGetrfiDriver<_Val, Trans::TRANS>;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_DRIVER_HH_
