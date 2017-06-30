////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/geqrfg.hpp
/// @brief   The LAPACK GEQRFGF+ORGQR driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_HPP_
#define MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_HPP_

#include <mcnla/core/la/dense/driver/geqrfg.hh>
#include <mcnla/core/la/dense/routine/lacpy.hpp>
#include <mcnla/core/la/raw/lapack/geqrf.hpp>
#include <mcnla/core/la/raw/lapack/gelqf.hpp>
#include <mcnla/core/la/raw/lapack/orgqr.hpp>
#include <mcnla/core/la/raw/lapack/orglq.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::DenseGeqrfgDriver() noexcept
  : nrow_(0),
    ncol_(0),
    work_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::DenseGeqrfgDriver(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    work_(query(nrow, ncol)) {
  mcnla_assert_gt(nrow_, 0);
  mcnla_assert_gt(ncol_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::DenseGeqrfgDriver(
    const MatrixType &a
) noexcept
  : DenseGeqrfgDriver(a.nrow(), a.ncol()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _TypeA, class _TypeTau, class _TypeQ, class _TypeR>
void DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::operator()(
    _TypeA   &&a,
    _TypeTau &&tau,
    _TypeQ   &&q,
    _TypeR   &&r
#else  // DOXYGEN_SHOULD_SKIP_THIS
void DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::operator()(
    MatrixType &a,
    VectorType &tau,
    MatrixType &q,
    MatrixType &r
#endif  // DOXYGEN_SHOULD_SKIP_THIS
) noexcept {
  compute(a, tau, q, r);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans> template <typename ..._Args>
void DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
std::tuple<index_t, index_t> DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::sizes() const noexcept {
  return std::make_tuple(nrow_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns of the orthogonal matrix Q.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
index_t DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::ncolQ() const noexcept {
  return std::min(nrow_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
DenseVector<_Val>& DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
const DenseVector<_Val>& DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the inverse of an general matrix using LU factorization.
///
/// @attention  Matrix @a a will be destroyed!
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
void DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::compute(
    MatrixType &a,
    VectorType &tau,
    MatrixType &q,
    MatrixType &r
) noexcept {
  mcnla_assert_eq(a.sizes(), this->sizes());
  mcnla_assert_eq(tau.len(), ncolQ());

  if ( _jobq == 'S' ) {
    mcnla_assert_eq(q.sizes(), std::make_tuple(nrow_, ncolQ()));
  }

  if ( _jobr == 'S' ) {
    mcnla_assert_eq(r.sizes(), std::make_tuple(ncolQ(), ncol_));
  }

  if ( !isTrans(_trans) ) {
    mcnla_assert_pass(detail::geqrf(nrow_, ncol_, a.valPtr(), a.pitch(), tau.valPtr(), work_.valPtr(), work_.len()));
  } else {
    mcnla_assert_pass(detail::gelqf(ncol_, nrow_, a.valPtr(), a.pitch(), tau.valPtr(), work_.valPtr(), work_.len()));
  }

  if ( _jobr == 'S' ) {
    if ( !isTrans(_trans) ) {
      detail::lacpy('U', ncolQ(), ncol_, a.valPtr(), a.pitch(), r.valPtr(), r.pitch());
    } else {
      detail::lacpy('L', ncolQ(), ncol_, a.valPtr(), a.pitch(), r.valPtr(), r.pitch());
    }
  }

  if ( _jobq == 'S' ) {
    copy(a, q);
    if ( !isTrans(_trans) ) {
      mcnla_assert_pass(detail::orgqr(nrow_, ncolQ(), ncolQ(), q.valPtr(), q.pitch(),
                                      tau.valPtr(), work_.valPtr(), work_.len()));
    } else {
      mcnla_assert_pass(detail::orglq(ncolQ(), nrow_, ncolQ(), q.valPtr(), q.pitch(),
                                      tau.valPtr(), work_.valPtr(), work_.len()));
    }
  } else if ( _jobq == 'O' ) {
    if ( !isTrans(_trans) ) {
      mcnla_assert_pass(detail::orgqr(nrow_, ncolQ(), ncolQ(), a.valPtr(), a.pitch(),
                                      tau.valPtr(), work_.valPtr(), work_.len()));
    } else {
      mcnla_assert_pass(detail::orglq(ncolQ(), nrow_, ncolQ(), a.valPtr(), a.pitch(),
                                      tau.valPtr(), work_.valPtr(), work_.len()));
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <JobOption _jobq, JobOption _jobr, typename _Val, Trans _trans>
index_t DenseGeqrfgDriver<_jobq, _jobr, _Val, _trans>::query(
    const index_t nrow_,
    const index_t ncol_
) noexcept {
  ValType lwork1 = 0, lwork2 = 0;

  if ( !isTrans(_trans) ) {
    mcnla_assert_pass(detail::geqrf(nrow_, ncol_, nullptr, nrow_, nullptr, &lwork1, -1));
  } else {
    mcnla_assert_pass(detail::gelqf(ncol_, nrow_, nullptr, ncol_, nullptr, &lwork1, -1));
  }

  if ( _jobq != 'N' ) {
    if ( !isTrans(_trans) ) {
      mcnla_assert_pass(detail::orgqr(nrow_, ncolQ(), ncolQ(), nullptr, nrow_, nullptr, &lwork2, -1));
    } else {
      mcnla_assert_pass(detail::orglq(ncolQ(), nrow_, ncolQ(), nullptr, ncol_, nullptr, &lwork2, -1));
    }
  }

  return std::max(lwork1, lwork2);
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GEQRFG_HPP_
