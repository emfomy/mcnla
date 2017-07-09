////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/parameters.hpp
/// @brief   The parameter structure of iSVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CORE_PARAMETERS_HPP_
#define MCNLA_ISVD_CORE_PARAMETERS_HPP_

#include <mcnla/isvd/core/parameters.hh>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor

template<typename _Val>
Parameters<_Val>::Parameters(
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) noexcept
  : mpi_comm(mpi_comm),
    mpi_size(mpi::commSize(mpi_comm)),
    mpi_root(mpi_root),
    mpi_rank(mpi::commRank(mpi_comm)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Synchronize the parameters
///
template<typename _Val>
void Parameters<_Val>::sync() noexcept {
  MPI_Bcast(&params_, sizeof(params_), MPI_BYTE, mpi_root, mpi_comm);
  synchronized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the parameters is synchronized.
///
template<typename _Val>
bool Parameters<_Val>::isSynchronized() const noexcept {
  return synchronized_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix.
///
template<typename _Val>
index_t Parameters<_Val>::nrow() const noexcept {
  return params_.nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns of the matrix.
///
template<typename _Val>
index_t Parameters<_Val>::ncol() const noexcept {
  return params_.ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows in this MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::nrowRank() const noexcept {
  return rowrange().len();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns in this MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::ncolRank() const noexcept {
  return colrange().len();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows in per MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::nrowEach() const noexcept {
  return (nrow()-1) / mpi_size + 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns in per MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::ncolEach() const noexcept {
  return (ncol()-1) / mpi_size + 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the total number of rows in all MPI nodes.
///
template<typename _Val>
index_t Parameters<_Val>::nrowTotal() const noexcept {
  return nrowEach() * mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the total number of columns in all MPI nodes.
///
template<typename _Val>
index_t Parameters<_Val>::ncolTotal() const noexcept {
  return ncolEach() * mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index range of the rows in this MPI node.
///
template<typename _Val>
IdxRange Parameters<_Val>::rowrange() const noexcept {
  auto range = I_{mpi_rank, mpi_rank+1} * nrowEach();
  if ( range.begin > nrow() ) { range.begin = nrow(); }
  if ( range.end > nrow() ) { range.end = nrow(); }
  return range;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index range of the columns in this MPI node.
///
template<typename _Val>
IdxRange Parameters<_Val>::colrange() const noexcept {
  auto range = I_{mpi_rank, mpi_rank+1} * ncolEach();
  if ( range.begin > ncol() ) { range.begin = ncol(); }
  if ( range.end > ncol() ) { range.end = ncol(); }
  return range;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the desired rank of approximate SVD.
///
template<typename _Val>
index_t Parameters<_Val>::rank() const noexcept {
  return params_.rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the oversampling dimension.
///
template<typename _Val>
index_t Parameters<_Val>::overRank() const noexcept {
  return params_.over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimension of random sketches.
///
template<typename _Val>
index_t Parameters<_Val>::dimSketch() const noexcept {
  return params_.rank_ + params_.over_rank_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the total dimension of random sketches per MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::dimSketchEach() const noexcept {
  return dimSketch() * numSketchEach();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the total dimension of random sketches.
///
template<typename _Val>
index_t Parameters<_Val>::dimSketchTotal() const noexcept {
  return dimSketch() * numSketch();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches of all MPI nodes.
///
template<typename _Val>
index_t Parameters<_Val>::numSketch() const noexcept {
  return params_.num_sketch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches per MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::numSketchEach() const noexcept {
  mcnla_assert_eq(params_.num_sketch_ % mpi_size, 0)
  return params_.num_sketch_ / mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the sizes of the matrix.
///
template<typename _Val> template <class _Matrix>
Parameters<_Val>& Parameters<_Val>::setSize(
    const _Matrix &matrix
) noexcept {
  return setSize(matrix.nrow(), matrix.ncol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSize
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setSize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  params_.nrow_ = nrow;
  params_.ncol_ = ncol;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the desired rank of approximate SVD.
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setRank(
    const index_t rank
) noexcept {
  params_.rank_ = rank;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the dimension of random sketches.
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setOverRank(
    const index_t over_rank
  ) noexcept {
  params_.over_rank_ = over_rank;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of total random sketches.
///
/// @attention  @a num_sketch must be a multiple of @ref mcnla::mpi::commSize "mpi_size"
///             unless all stages are row-block version.
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setNumSketch(
    const index_t num_sketch
) noexcept {
  params_.num_sketch_ = num_sketch;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of random sketches per MPI node.
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setNumSketchEach(
    const index_t num_sketch_each
) noexcept {
  params_.num_sketch_ = num_sketch_each * mpi_size;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix A.
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixA() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowTotal(), ncol());
  return retval({0_i, nrow()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Aj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixAj() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowEach(), ncol());
  return retval({0_i, nrowRank()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix collection Q.
///
template<typename _Val>
DenseMatrixCollectionColBlockRowMajor<_Val> Parameters<_Val>::createCollectionQ() const noexcept {
  DenseMatrixCollectionColBlockRowMajor<_Val> retval(nrowTotal(), dimSketch(), numSketchEach());
  return retval({0_i, nrow()}, ""_, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixCollectionColBlockRowMajor<_Val> Parameters<_Val>::createCollectionQj() const noexcept {
  DenseMatrixCollectionColBlockRowMajor<_Val> retval(nrowEach(), dimSketch(), numSketch());
  return retval({0_i, nrowRank()}, ""_, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Q.
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixQbar() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowTotal(), dimSketch());
  return retval({0_i, nrow()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Qj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixQbarj() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowEach(), dimSketch());
  return retval({0_i, nrowRank()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix U.
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixU() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowTotal(), rank());
  return retval({0_i, nrow()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Uj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixUj() const noexcept {
  DenseMatrixRowMajor<_Val> retval(nrowEach(), rank());
  return retval({0_i, nrowRank()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix V.
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixV() const noexcept {
  DenseMatrixRowMajor<_Val> retval(ncolTotal(), rank());
  return retval({0_i, ncol()}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Vj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixVj() const noexcept {
  DenseMatrixRowMajor<_Val> retval(ncolEach(), rank());
  return retval({0_i, ncolRank()}, ""_);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_PARAMETERS_HPP_
