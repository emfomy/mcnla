////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_gramian_kolmogorov_nagumo_integrator.hh
/// @brief   The definition of Gramian Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

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
struct RowBlockGramianKolmogorovNagumoIntegratorTag {};
template <typename _Val>
using RowBlockGramianKolmogorovNagumoIntegrator = Integrator<RowBlockGramianKolmogorovNagumoIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Gramian Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Integrator<RowBlockGramianKolmogorovNagumoIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockGramianKolmogorovNagumoIntegrator
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockGramianKolmogorovNagumoIntegrator<_Val>> {

  friend StageWrapper<RowBlockGramianKolmogorovNagumoIntegrator<_Val>>;

  static_assert(traits::ValTraits<_Val>::is_real, "Kolmogorov-Nagumo-type integrator dost not support complex value!");

 private:

  using BaseType = StageWrapper<RowBlockGramianKolmogorovNagumoIntegrator<_Val>>;

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

  /// The matrix Bs.
  DenseMatrixRowMajor<_Val> matrix_bs_;

  /// The matrix Bc and B+.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_bc_;

  /// The matrix Bgc.
  DenseMatrixRowMajor<_Val> matrix_bgc_;

  /// The matrix Dc.
  DenseMatrixRowMajor<_Val> matrix_dc_;

  /// The matrix Z.
  DenseSymmetricMatrixRowMajor<_Val> symatrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<_Val> matrix_c_;

  /// The matrix inv(C).
  DenseSymmetricMatrixRowMajor<_Val> symatrix_cinv_;

  /// The matrix ~F.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_ff_;

  /// The matrix ~E.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_ee_;

  /// The vector S.
  DenseVector<_Val> vector_s_;

  /// The vector sqrt(S).
  DenseVector<_Val> vector_ss_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<_Val>, 'V'> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Integrator( const Parameters<_Val> &parameters,
                     const index_t max_iteration = 256, const RealValT<_Val> tolerance = 1e-4 ) noexcept;

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

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
