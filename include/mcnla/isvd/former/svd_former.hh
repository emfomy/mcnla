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
/// @ingroup  isvd_former_module_detail
/// The SVD former tag.
///
struct SvdFormerTag {};

/// @ingroup  isvd_former_module
template <typename _Val>
using SvdFormer = Former<SvdFormerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The SVD former.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Former<SvdFormerTag, _Val>
  : public FormerWrapper<SvdFormer<_Val>> {

  friend FormerWrapper<SvdFormer<_Val>>;

 private:

  using BaseType = FormerWrapper<SvdFormer<_Val>>;

 public:

  using ValType        = _Val;
  using RealValType = RealValT<ValType>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Standard Former";

  /// The starting time
  double moment0_;

  /// The ending time of Q' * A
  double moment1_;

  /// The ending time of SVD
  double moment2_;

  /// The ending time of Q * W
  double moment3_;

  /// The matrix W.
  DenseMatrixColMajor<ValType> matrix_w_;

  /// The vector S.
  DenseVector<RealValType> vector_s_;

  /// The cut vector S.
  DenseVector<RealValType> vector_s_cut_;

  /// The matrix U.
  DenseMatrixColMajor<ValType> matrix_u_;

  /// The cut matrix U.
  DenseMatrixColMajor<ValType> matrix_u_cut_;

  /// The matrix Vt.
  DenseMatrixColMajor<ValType> matrix_vt_;

  /// The cut matrix Vt.
  DenseMatrixColMajor<ValType> matrix_vt_cut_;

  /// The empty matrix.
  DenseMatrixColMajor<ValType> matrix_empty_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixColMajor<ValType>, 'S', 'O'> gesvd_driver_;

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
  void formImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_qc ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorSImpl() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixUImpl() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVtImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HH_
