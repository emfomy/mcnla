////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/syev.hh
/// @brief   The definition of LAPACK SYEV driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_SYEV_DRIVER_HH_
#define MCNLA_CORE_LA_DENSE_DRIVER_SYEV_DRIVER_HH_

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
/// @brief  The eigenvalue decomposition driver of symmetric / Hermitian matrices.
///
/// @tparam  _Matrix  The matrix type.
///
/// @see  mcnla::la::syev
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
class DenseSyevDriver {

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  using ValType        = _Val;
  using MatrixType     = DenseSymmetricMatrix<_Val, _trans, _uplo>;
  using VectorType     = DenseVector<_Val>;
  using RealVectorType = DenseVector<RealValT<_Val>>;

  static constexpr bool is_real = traits::ValTraits<ValType>::is_real;

 protected:

  /// The dimension.
  index_t size_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructor
  inline DenseSyevDriver() noexcept;
  inline DenseSyevDriver( const index_t size ) noexcept;
  inline DenseSyevDriver( const MatrixType &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeW>
  inline void operator()( _TypeA &&a, _TypeW &&w ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeW>
  inline void computeValues( _TypeA &&a, _TypeW &&w ) noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t, index_t> sizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  template <JobOption __jobz = _jobz>
  inline void compute( MatrixType &a, RealVectorType &w ) noexcept;

  // Queries workspace size
  inline index_t query( const index_t size ) noexcept;

};

/// @ingroup  la_dense_lapack_ls_module
/// @see  DenseSyevDriver
template <JobOption _jobz, typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSyevDriverColMajor = DenseSyevDriver<_jobz, _Val, Trans::NORMAL, _uplo>;

/// @ingroup  la_dense_lapack_ls_module
template <JobOption _jobz, typename _Val, Uplo _uplo = Uplo::LOWER>
/// @see  DenseSyevDriver
using DenseSyevDriverRowMajor = DenseSyevDriver<_jobz, _Val, Trans::TRANS, _uplo>;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_SYEV_DRIVER_HH_
