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
/// @brief  The eigenvalue driver of symmetric / Hermitian matrices.
///
/// @tparam  _Matrix  The matrix type.
///
/// @see  mcnla::la::syev
///
template <class _Matrix, JobOption _jobz>
class SyevDriver {

  assertDenseSymmetricMatrix(_Matrix);

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  static constexpr Trans trans = _Matrix::trans;
  static constexpr Uplo  uplo  = _Matrix::uplo;

  using ValType        = ValT<_Matrix>;
  using VectorType     = VectorT<_Matrix>;
  using RealVectorType = RealT<VectorT<_Matrix>>;
  using MatrixType     = _Matrix;

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
  inline SyevDriver() noexcept;
  inline SyevDriver( const index_t size ) noexcept;
  inline SyevDriver( const MatrixType &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeW>
  inline void operator()( _TypeA &&a, _TypeW &&w ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeW>
  inline void computeValues( _TypeA &&a, _TypeW &&w ) noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t> sizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  template <JobOption __jobz = _jobz>
  inline void compute( MatrixType &a, RealVectorType &w ) noexcept;

  // Queries
  inline index_t query( const index_t size ) noexcept;

};

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_SYEV_DRIVER_HH_
