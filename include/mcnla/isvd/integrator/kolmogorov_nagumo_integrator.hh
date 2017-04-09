////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hh
/// @brief   The definition of Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

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
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator tag.
///
struct KolmogorovNagumoIntegratorTag {};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using KolmogorovNagumoIntegrator = Integrator<KolmogorovNagumoIntegratorTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Val  The scalar type.
///
template <typename _Val>
class Integrator<KolmogorovNagumoIntegratorTag, _Val>
  : public ComponentWrapper<Integrator<KolmogorovNagumoIntegratorTag, _Val>> {

  friend ComponentWrapper<Integrator<KolmogorovNagumoIntegratorTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Integrator<KolmogorovNagumoIntegratorTag, _Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Kolmogorov-Nagumo-Type Integrator";

  /// The maximum number of iteration.
  index_t max_iteration_;

  /// The tolerance of convergence condition.
  RealValType tolerance_;

  /// The number of iteration.
  index_t iteration_;

  /// The communication time of iterating.
  double time2c_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ValType> matrix_bs_;

  /// The matrix D.
  DenseMatrixRowMajor<ValType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ValType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ValType> matrix_c_;

  /// The matrix X.
  DenseMatrixRowMajor<ValType> matrix_x_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ValType> matrix_tmp_;

  /// The vector E.
  DenseVector<ValType> vector_e_;

  /// The vector F.
  DenseVector<ValType> vector_f_;

  /// The SYEV engine.
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
  void runImpl( const DenseMatrixCollection120<ValType> &collection_q, DenseMatrixRowMajor<ValType> &matrix_qbar ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
