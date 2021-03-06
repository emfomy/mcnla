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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Integrator
  #define MCNLA_ALIAS1 Integrator<KolmogorovNagumoIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 KolmogorovNagumoIntegrator
  #define MCNLA_ALIAS1 KolmogorovNagumoIntegrator
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
struct KolmogorovNagumoIntegratorTag {};
template <typename _Val> using KolmogorovNagumoIntegrator = Integrator<KolmogorovNagumoIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Val  The scalar type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<KolmogorovNagumoIntegrator<_Val>> {

  friend StageWrapper<KolmogorovNagumoIntegrator<_Val>>;

  static_assert(traits::ValTraits<_Val>::is_real, "Kolmogorov-Nagumo-type integrator dost not support complex value!");

 private:

  using BaseType = StageWrapper<KolmogorovNagumoIntegrator<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Kolmogorov-Nagumo-Type Integrator";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "copying Qc / iterating";

  /// The maximum number of iteration.
  index_t max_iteration_;

  /// The tolerance of convergence condition.
  RealValT<_Val> tolerance_;

  /// The number of iteration.
  index_t iteration_;

  /// The matrix B.
  DenseMatrixRowMajor<_Val> matrix_b_;

  /// The matrix D.
  DenseMatrixRowMajor<_Val> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<_Val> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<_Val> matrix_c_;

  /// The matrix X.
  DenseMatrixRowMajor<_Val> matrix_x_;

  /// The temporary matrix.
  DenseMatrixRowMajor<_Val> matrix_tmp_;

  /// The vector E.
  DenseVector<_Val> vector_e_;

  /// The vector F.
  DenseVector<_Val> vector_f_;

  /// The SYEV engine.
  la::DenseSyevDriverRowMajor<'V', _Val> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters,
                     const index_t max_iteration = 256, const RealValT<_Val> tolerance = 1e-4 ) noexcept;

  // Gets parameters
  inline index_t        maxIteration() const noexcept;
  inline RealValT<_Val> tolerance() const noexcept;
  inline index_t        iteration() const noexcept;

  // Sets parameters
  inline MCNLA_ALIAS1& setMaxIteration( const index_t max_iteration ) noexcept;
  inline MCNLA_ALIAS1& setTolerance( const RealValT<_Val> tolerance ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q,
                      DenseMatrixRowMajor<_Val> &matrix_qbar ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
