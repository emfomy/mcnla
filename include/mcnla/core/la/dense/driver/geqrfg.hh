////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/geqrfg.hh
/// @brief   The definition of LAPACK GEQRF+ORGQR driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_DRIVER_HH_
#define MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_DRIVER_HH_

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
/// @ingroup  la_dense_lapack_ls_module
/// @brief  The QR-orthogonalization driver of general matrices.
///
/// @note  This driver runs GEQRF and ORGQR.
///
template <typename _Val, Trans _trans>
class DenseGeqrfgDriver {

 private:

  using ValType    = _Val;
  using MatrixType = DenseMatrix<_Val, _trans>;
  using VectorType = DenseVector<_Val>;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The elementary reflectors.
  VectorType tau_;

  /// The workspace.
  VectorType work_;

 public:

  // Constructors
  inline DenseGeqrfgDriver() noexcept;
  inline DenseGeqrfgDriver( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseGeqrfgDriver( const MatrixType &a ) noexcept;

  // Operators
  inline void operator()( MatrixType &a ) noexcept;
  inline void operator()( MatrixType &&a ) noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t, index_t> sizes() const noexcept;
  inline index_t ncolQ() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;

 protected:

  // Computes
  inline void compute( MatrixType &a ) noexcept;

  // Queries workspace size
  inline index_t query( const index_t nrow, const index_t ncol ) noexcept;

};

/// @ingroup  la_dense_lapack_ls_module
/// @see  DenseGeqrfgDriver
template <typename _Val>
using DenseGeqrfgDriverColMajor = DenseGeqrfgDriver<_Val, Trans::NORMAL>;

/// @ingroup  la_dense_lapack_ls_module
template <typename _Val>
/// @see  DenseGeqrfgDriver
using DenseGeqrfgDriverRowMajor = DenseGeqrfgDriver<_Val, Trans::TRANS>;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_DRIVER_HH_
