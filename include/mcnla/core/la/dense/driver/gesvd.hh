////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/gesvd.hh
/// @brief   The definition of LAPACK GESVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GESVD_DRIVER_HH_
#define MCNLA_CORE_LA_DENSE_DRIVER_GESVD_DRIVER_HH_

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
/// @brief  The singular value decomposition driver of general rectangular matrices.
///
/// @see  mcnla::la::gesvd
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
class GesvdDriver {

  assertDenseMatrix(_Matrix);

  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");

 private:

  static constexpr Trans trans = _Matrix::trans;

  using ValType        = ValT<_Matrix>;
  using VectorType     = VectorT<_Matrix>;
  using RealVectorType = RealT<VectorT<_Matrix>>;
  using MatrixType     = _Matrix;

  static constexpr bool is_real = traits::ValTraits<ValType>::is_real;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

  /// Empty matrix.
  MatrixType matrix_empty_;

 public:

  // Constructors
  inline GesvdDriver() noexcept;
  inline GesvdDriver( const index_t nrow, const index_t ncol ) noexcept;
  inline GesvdDriver( const MatrixType &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
  inline void operator()( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept;

  // Computes singular values
  template <class _TypeA, class _TypeS>
  inline void computeValues( _TypeA &&a, _TypeS &&s ) noexcept;

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
  template <JobOption __jobu = _jobu, JobOption __jobvt = _jobvt>
  inline void compute( MatrixType &a, RealVectorType &s, MatrixType &u, MatrixType &vt ) noexcept;

  // Queries
  inline index_t query( const index_t nrow, const index_t ncol ) noexcept;

};

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GESVD_DRIVER_HH_
