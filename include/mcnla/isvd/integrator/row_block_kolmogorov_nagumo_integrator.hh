////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hh
/// @brief   The definition of Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

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
/// The row-block Kolmogorov-Nagumo-type integrator tag.
///
struct RowBlockKolmogorovNagumoIntegratorTag {};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using RowBlockKolmogorovNagumoIntegrator = Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>
  : public ComponentWrapper<RowBlockKolmogorovNagumoIntegrator<_Val>> {

  friend ComponentWrapper<RowBlockKolmogorovNagumoIntegrator<_Val>>;

 private:

  using BaseType = ComponentWrapper<RowBlockKolmogorovNagumoIntegrator<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Kolmogorov-Nagumo-Type Integrator (Row-Block Version)";

  /// The maximum number of iteration.
  index_t max_iteration_;

  /// The tolerance of convergence condition.
  RealValType tolerance_;

  /// The number of iteration.
  index_t iteration_;

  /// The communication time of iterating.
  double time2c_;

  /// The matrix Qs.
  DenseMatrixRowMajor<ValType> matrix_qs_;

  /// The matrix Qjs.
  DenseMatrixRowMajor<ValType> matrix_qjs_;

  /// The matrix Qcj.
  DenseMatrixRowMajor<ValType> matrix_qcj_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ValType> matrix_bs_;

  /// The matrix D.
  DenseMatrixRowMajor<ValType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ValType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ValType> matrix_c_;

  /// The matrix Xj.
  DenseMatrixRowMajor<ValType> matrix_xj_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ValType> matrix_tmp_;

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

 public:

  // Constructor
  inline Integrator( const Parameters<ValType> &parameters,
                     const index_t max_iteration = 256, const RealValType tolerance = 1e-4 ) noexcept;

  // Gets parameters
  inline index_t     maxIteration() const noexcept;
  inline RealValType tolerance() const noexcept;
  inline index_t     iteration() const noexcept;
  inline double      time2c() const noexcept;

  // Sets parameters
  inline Integrator& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Integrator& setTolerance( const RealValType tolerance ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollection120<ValType> &collection_qj, DenseMatrixRowMajor<ValType> &matrix_qbarj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
