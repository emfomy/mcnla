////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/geqrfg.hh
/// @brief   The definition of LAPACK GEQRFGF+ORGQR driver.
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
/// @brief  The QR decomposition driver of general matrices.
///
/// @note  This driver runs GEQRFGF and ORGQR.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
class DenseGeqrfgDriver {

  static_assert(_jobq == 'S' || _jobq == 'O' || _jobq == 'N', "Job undefined!");
  static_assert(_jobr == 'S' || _jobr == 'O' || _jobr == 'N', "Job undefined!");
  static_assert(_jobq != 'O' || _jobr != 'O', "Job conflict!");

 private:

  using ValType    = _Val;
  using MatrixType = DenseMatrix<_Val, _trans>;
  using VectorType = DenseVector<_Val>;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The workspace.
  VectorType work_;

 public:

  // Constructors
  inline DenseGeqrfgDriver() noexcept;
  inline DenseGeqrfgDriver( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseGeqrfgDriver( const MatrixType &a ) noexcept;

  // Operators
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  template <class _TypeA, class _TypeTau, class _TypeQ, class _TypeR>
  inline void operator()( _TypeA &&a, _TypeTau &&tau, _TypeQ &&q, _TypeR &&r ) noexcept;
#else  // DOXYGEN_SHOULD_SKIP_THIS
  inline void operator()( MatrixType &a, VectorType &tau, MatrixType &q, MatrixType &r ) noexcept;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
  inline void compute( MatrixType &a, VectorType &tau, MatrixType &q, MatrixType &r ) noexcept;

  // Queries workspace size
  inline index_t query( const index_t nrow, const index_t ncol ) noexcept;

};

/// @ingroup  la_dense_lapack_ls_module
/// @see  DenseGeqrfgDriver
template <JobOption _jobq, JobOption _jobr, typename _Val>
using DenseGeqrfgDriverColMajor = DenseGeqrfgDriver<_jobq, _jobr, _Val, Trans::NORMAL>;

/// @ingroup  la_dense_lapack_ls_module
template <JobOption _jobq, JobOption _jobr, typename _Val>
/// @see  DenseGeqrfgDriver
using DenseGeqrfgDriverRowMajor = DenseGeqrfgDriver<_jobq, _jobr, _Val, Trans::TRANS>;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_DRIVER_HH_
