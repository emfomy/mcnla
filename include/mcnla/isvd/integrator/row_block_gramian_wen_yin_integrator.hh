////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_gramian_wen_yin_integrator.hh
/// @brief   The definition of Gramian Wen-Yin line search integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HH_

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct RowBlockGramianWenYinIntegratorTag {};
template <typename _Val>
using RowBlockGramianWenYinIntegrator = Integrator<RowBlockGramianWenYinIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Gramian Wen-Yin line search integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Integrator<RowBlockGramianWenYinIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockGramianWenYinIntegrator
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockGramianWenYinIntegrator<_Val>> {

  friend StageWrapper<RowBlockGramianWenYinIntegrator<_Val>>;

  static_assert(traits::ValTraits<_Val>::is_real, "Wen-Yin line search integrator dost not support complex value!");

 private:

  using BaseType = StageWrapper<RowBlockGramianWenYinIntegrator<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Kolmogorov-Nagumo-Type Integrator (Row-Block Gramian Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "initializing / iterating / forming Qbar";

  /// The maximum number of iteration.
  index_t max_iteration_;

  /// The tolerance of convergence condition.
  RealValT<_Val> tolerance_;

  /// The number of iteration.
  index_t iteration_;

  /// The initial step size.
  _Val tau0_ = 1.0;

  /// The maximum predicting step size.
  _Val taumax_ = 1e14;

  /// The minimum predicting step size.
  _Val taumin_ = 1e-14;

  /// The maximum number of iteration in predicting step size.
  index_t taumaxiter_ = 20;

  /// The scaling parameter for step size searching.
  _Val beta_ = 0.5;

  /// The parameter for step size searching.
  _Val sigma_ = 1e-4;

  /// The parameter for next step searching.
  _Val eta_ = 0.85;

  /// The matrix Bs.
  DenseMatrixRowMajor<_Val> matrix_bs_;

  /// The matrix Bc and B+.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_bc_;

  /// The matrix Bgc.
  DenseMatrixRowMajor<_Val> matrix_bgc_;

  /// The matrix Dc and D+.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_dc_;

  /// The matrix Dgc.
  DenseMatrixRowMajor<_Val> matrix_dgc_;

  /// The matrix C.
  DenseMatrixRowMajor<_Val> matrix_c_;

  /// The matrix ~F.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_ff_;

  /// The matrix ~E.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_ee_;

  /// The matrix Phi1.
  DenseMatrixRowMajor<_Val> matrix_phi1_;

  /// The matrix Phi2.
  DenseMatrixRowMajor<_Val> matrix_phi2_;

  /// The matrix Upsilon1.
  DenseMatrixRowMajor<_Val> matrix_upsolon1_;

  /// The matrix Upsilon2.
  DenseMatrixRowMajor<_Val> matrix_upsolon2_;

  /// The matrix Bc' * Upsilon1.
  DenseMatrixRowMajor<_Val> matrix_bct_upsolon1_;

  /// The matrix Bc' * Upsilon2.
  DenseMatrixRowMajor<_Val> matrix_bct_upsolon2_;

  /// The matrix Bs * Upsilon.
  DenseMatrixRowMajor<_Val> matrix_bs_upsolon_;

  /// The GETRFI driver.
  la::DenseGetrfiDriverRowMajor<_Val> getrfi_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Integrator( const Parameters<_Val> &parameters,
                     const index_t max_iteration = 256, const RealValT<_Val> tolerance = 1e-3 ) noexcept;

  // Gets parameters
  inline index_t        maxIteration() const noexcept;
  inline RealValT<_Val> tolerance() const noexcept;
  inline index_t        iteration() const noexcept;

  // Sets parameters
  inline Integrator& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Integrator& setTolerance( const RealValT<_Val> tolerance ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
                      DenseMatrixRowMajor<_Val> &matrix_qbarj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HH_
