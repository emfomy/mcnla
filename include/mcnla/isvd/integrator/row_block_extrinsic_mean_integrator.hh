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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Integrator
  #define MCNLA_ALIAS1 Integrator<RowBlockExtrinsicMeanIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 RowBlockExtrinsicMeanIntegrator
  #define MCNLA_ALIAS1 RowBlockExtrinsicMeanIntegrator
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct RowBlockExtrinsicMeanIntegratorTag {};
template <typename _Val> using RowBlockExtrinsicMeanIntegrator = Integrator<RowBlockExtrinsicMeanIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The extrinsic mean integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>> {

  friend StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockExtrinsicMeanIntegrator<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Kolmogorov-Nagumo-Type Integrator (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "Rotate / Flip / Sum";

  /// The matrix Bsj.
  DenseMatrixRowMajor<_Val> matrix_bsj_;

  /// The collection Bi.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_bi_;

  /// The collection Bi0.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_bi0_;

  /// The collection G.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_g_;

  /// The matrix G0.
  DenseMatrixRowMajor<_Val> matrix_g0_;

  /// The matrix GB (= G0 * Bi0').
  DenseMatrixRowMajor<_Val> matrix_gb_;

  /// The vector S.
  DenseVector<_Val> vector_s_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The SYEV driver.
  la::DenseSyevDriverRowMajor<'V', _Val> syev_driver_;

  /// The GESVD driver.
  la::DenseGesvdDriverRowMajor<'O', 'N', _Val> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
                const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q,
                      DenseMatrixRowMajor<_Val> &matrix_qbar ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HH_
