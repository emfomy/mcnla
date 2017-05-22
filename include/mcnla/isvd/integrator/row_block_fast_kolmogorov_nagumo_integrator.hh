////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_fast_kolmogorov_nagumo_integrator.hh
/// @brief   The definition of Kolmogorov-Nagumo-type integrator (fast row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_FAST_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_FAST_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

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
struct RowBlockFastKolmogorovNagumoIntegratorTag {};
template <typename _Val>
using RowBlockFastKolmogorovNagumoIntegrator = Integrator<RowBlockFastKolmogorovNagumoIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator (fast row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Integrator<RowBlockFastKolmogorovNagumoIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockFastKolmogorovNagumoIntegrator
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockFastKolmogorovNagumoIntegrator<_Val>> {

  friend StageWrapper<RowBlockFastKolmogorovNagumoIntegrator<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockFastKolmogorovNagumoIntegrator<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Kolmogorov-Nagumo-Type Integrator (Fast Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "initializing / iterating / forming Qbar";

  /// The maximum number of iteration.
  index_t max_iteration_;

  /// The tolerance of convergence condition.
  RealValType tolerance_;

  /// The number of iteration.
  index_t iteration_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ValType> matrix_bs_;

  /// The matrix B.
  DenseMatrixCollection102<ValType> collection_b_;

  /// The matrix D.
  DenseMatrixRowMajor<ValType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ValType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ValType> matrix_c_;

  /// The matrix inv(C).
  DenseMatrixRowMajor<ValType> matrix_cinv_;

  /// The matrix Sf.
  DenseMatrixCollection012<ValType> collection_sf_;

  /// The matrix Tf.
  DenseMatrixCollection012<ValType> collection_tf_;

  /// The vector E.
  DenseVector<ValType> vector_e_;

  /// The vector F.
  DenseVector<ValType> vector_f_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<ValType>, 'V'> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Integrator( const Parameters<ValType> &parameters,
                     const index_t max_iteration = 256, const RealValType tolerance = 1e-4 ) noexcept;

  // Gets parameters
  inline index_t     maxIteration() const noexcept;
  inline RealValType tolerance() const noexcept;
  inline index_t     iteration() const noexcept;

  // Sets parameters
  inline Integrator& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Integrator& setTolerance( const RealValType tolerance ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollection201<ValType> &collection_qj, DenseMatrixRowMajor<ValType> &matrix_qbarj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_FAST_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
