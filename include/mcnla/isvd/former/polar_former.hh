////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/polar_former.hh
/// @brief   The definition of Polar former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_POLAR_FORMER_HH_
#define MCNLA_ISVD_FORMER_POLAR_FORMER_HH_

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
/// The Polar former tag.
///
struct PolarFormerTag {};

/// @ingroup  isvd_former_module
template <typename _Val>
using PolarFormer = Former<PolarFormerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The Polar former.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Former<PolarFormerTag, _Val>
  : public ComponentWrapper<PolarFormer<_Val>> {

  friend ComponentWrapper<PolarFormer<_Val>>;

 private:

  using BaseType = ComponentWrapper<PolarFormer<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Polar Former";

  /// The matrix W.
  DenseMatrixColMajor<ValType> matrix_w_;

  /// The cut matrix W.
  DenseMatrixColMajor<ValType> matrix_w_cut_;

  /// The vector S.
  DenseVector<RealValType> vector_s_;

  /// The cut vector S.
  DenseVector<RealValType> vector_s_cut_;

  /// The cut matrix U.
  DenseMatrixColMajor<ValType> matrix_u_cut_;

  /// The matrix Q'*A.
  DenseMatrixRowMajor<ValType> matrix_qta_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixColMajor<ValType>, 'V'> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Former( const Parameters<ValType> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorS() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixU() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVt() const noexcept = delete;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_POLAR_FORMER_HH_
