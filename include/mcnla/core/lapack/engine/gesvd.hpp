////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/engine/gesvd.hpp
/// @brief   The LAPACK GESVD engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ENGINE_GESVD_ENGINE_HPP_
#define MCNLA_CORE_LAPACK_ENGINE_GESVD_ENGINE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/lapack/def.hpp>
#include <tuple>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/lapack/lapack/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  lapack_driver_module
/// @brief  The singular value solver of general rectangular matrices.
///
/// @see mcnla::lapack::gesvd
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
class GesvdEngine {

  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");

 private:

  static constexpr Trans trans = _Matrix::trans;

  using ScalarType     = ScalarT<_Matrix>;
  using VectorType     = VectorT<_Matrix>;
  using RealVectorType = RealT<VectorT<_Matrix>>;
  using MatrixType     = _Matrix;

  static constexpr bool is_real = traits::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, trans>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

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
  inline GesvdEngine() noexcept;
  inline GesvdEngine( const index_t nrow, const index_t ncol ) noexcept;
  inline GesvdEngine( const MatrixType &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
  inline void operator()( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeS>
  inline void computeValues( _TypeA &&a, _TypeS &&s ) noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

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

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ENGINE_GESVD_ENGINE_HPP_
