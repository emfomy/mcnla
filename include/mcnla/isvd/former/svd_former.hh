////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hh
/// @brief   The definition of SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HH_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The SVD former tag.
///
struct SvdFormerTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
///
/// The SVD former.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Former<_Scalar, SvdFormerTag>
  : public FormerWrapper<Former<_Scalar, SvdFormerTag>> {

  friend FormerWrapper<Former<_Scalar, SvdFormerTag>>;

 private:

  using BaseType = FormerWrapper<Former<_Scalar, SvdFormerTag>>;

 public:

  using ScalarType     = _Scalar;
  using RealScalarType = RealScalarT<ScalarType>;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Standard Former";

  /// The starting time
  double time0_;

  /// The ending time of Q' * A
  double time1_;

  /// The ending time of SVD
  double time2_;

  /// The ending time of Q * W
  double time3_;

  /// The matrix W.
  DenseMatrixColMajor<ScalarType> matrix_w_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The cut vector S.
  DenseVector<RealScalarType> vector_s_cut_;

  /// The matrix U.
  DenseMatrixColMajor<ScalarType> matrix_u_;

  /// The cut matrix U.
  DenseMatrixColMajor<ScalarType> matrix_u_cut_;

  /// The matrix Vt.
  DenseMatrixColMajor<ScalarType> matrix_vt_;

  /// The cut matrix Vt.
  DenseMatrixColMajor<ScalarType> matrix_vt_cut_;

  /// The empty matrix.
  DenseMatrixColMajor<ScalarType> matrix_empty_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixColMajor<ScalarType>, 'S', 'O'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;

 public:

  // Constructor
  inline Former( const ParametersType &parameters, const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Gets time
  inline double time1() const noexcept;
  inline double time2() const noexcept;
  inline double time3() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void formImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ScalarType> &matrix_qc ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& vectorSImpl() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& matrixUImpl() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& matrixVtImpl() const noexcept;

};

/// @ingroup  isvd_former_module
template <typename _Scalar>
using SvdFormer = Former<_Scalar, SvdFormerTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HH_
