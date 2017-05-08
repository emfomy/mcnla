////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_extrinsic_mean_integrator.hh
/// @brief   The definition of extrinsic mean integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator.hpp>
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
/// The row-block extrinsic mean integrator tag.
///
struct RowBlockExtrinsicMeanIntegratorTag {};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using RowBlockExtrinsicMeanIntegrator = Integrator<RowBlockExtrinsicMeanIntegratorTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The extrinsic mean integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Integrator<RowBlockExtrinsicMeanIntegratorTag, _Val>
  : public StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>> {

  friend StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Kolmogorov-Nagumo-Type Integrator (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "Rotate / Flip / Sum";

  /// The matrix Bsj.
  DenseMatrixRowMajor<ValType> matrix_bsj_;

  /// The collection Bi.
  DenseMatrixCollection102<ValType> collection_bi_;

  /// The collection Bi0.
  DenseMatrixCollection102<ValType> collection_bi0_;

  /// The collection G.
  DenseMatrixCollection102<ValType> collection_g_;

  /// The matrix G0.
  DenseMatrixRowMajor<ValType> matrix_g0_;

  /// The matrix GB (= G0 * Bi0').
  DenseMatrixRowMajor<ValType> matrix_gb_;

  /// The vector S.
  DenseVector<ValType> vector_s_;

  /// The empty matrix.
  DenseMatrixRowMajor<ValType> matrix_empty_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<ValType>, 'V'> syev_driver_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixRowMajor<ValType>, 'O', 'N'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Integrator( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollection201<ValType> &collection_qj, const DenseMatrixCollection201<ValType> &collection_q,
                DenseMatrixRowMajor<ValType> &matrix_qbar ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HH_
