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
  : public ComponentWrapper<SvdFormer<_Val>> {

  friend ComponentWrapper<SvdFormer<_Val>>;

 private:

  using BaseType = ComponentWrapper<SvdFormer<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Standard Former";

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
  using BaseType::moments_;

 public:

  // Constructor
  inline Former( const Parameters<ValType> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorS() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixU() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVt() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HH_
