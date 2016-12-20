////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/reconstructor/reconstructor_base.hpp
/// @brief   The iSVD reconstructor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_
#define MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_reconstructor_module
///
/// The interface of iSVD reconstructor.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ReconstructorBase : public utility::CrtpBase<_Derived, ReconstructorBase<_Derived>> {

 public:

  using MatrixType     = typename traits::Traits<_Derived>::MatrixType;
  using ScalarType     = typename MatrixType::ScalarType;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// @copydoc  mcnla::isvd::solver::parameters_
  const Parameters<ScalarType> &parameters_;

  /// @copydoc  mcnla::isvd::solver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::solver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline ReconstructorBase( const Parameters<ScalarType> &parameters,
                            const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Reconstructs
  inline void reconstruct( const MatrixType &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* getName() const noexcept;

  // Gets compute time
  inline double getTime() const noexcept;
  inline const std::vector<double> getTimes() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorS() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixU() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVt() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_
