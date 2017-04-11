////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/core/parameters.hpp
/// @brief   The the parameter structure of iSVD driver.
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
/// @brief  Gets the number of rows of the matrix in this MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::nrowEach() const noexcept {
  return (mpi_rank != (mpi_size-1) ? nrowEach0() : nrowEachLast());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns of the matrix in this MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::ncolEach() const noexcept {
  return (mpi_rank != (mpi_size-1) ? ncolEach0() : ncolEachLast());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix in per MPI node (except last one).
///
template<typename _Val>
index_t Parameters<_Val>::nrowEach0() const noexcept {
  return nrow() / mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns of the matrix in per MPI node (except last one).
///
template<typename _Val>
index_t Parameters<_Val>::ncolEach0() const noexcept {
  return ncol() / mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of the matrix in the last MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::nrowEachLast() const noexcept {
  return nrow() / mpi_size + nrow() % mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns of the matrix in the last MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::ncolEachLast() const noexcept {
  return ncol() / mpi_size + ncol() % mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index range of the rows of the matrix in this MPI node.
///
template<typename _Val>
IdxRange Parameters<_Val>::rowrange() const noexcept {
  return (mpi_rank != (mpi_size-1) ? IdxRange{mpi_rank, mpi_rank+1} * nrowEach0() : IdxRange{mpi_rank * nrowEach0(), nrow()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index range of the columns of the matrix in this MPI node.
///
template<typename _Val>
IdxRange Parameters<_Val>::colrange() const noexcept {
  return (mpi_rank != (mpi_size-1) ? IdxRange{mpi_rank, mpi_rank+1} * ncolEach0() : IdxRange{mpi_rank * ncolEach0(), ncol()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a list of the staring row index of the matrix in each MPI node.
///
template<typename _Val>
std::vector<index_t> Parameters<_Val>::nrowEachs(
     const index_t size
) const noexcept {
  std::vector<index_t> retval(mpi_size);
  std::fill(retval.begin(), retval.end()-1, nrowEach0() * size);
  retval.back() = nrowEachLast() * size;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a list of the staring column index of the matrix in each MPI node.
///
template<typename _Val>
std::vector<index_t> Parameters<_Val>::ncolEachs(
     const index_t size
) const noexcept {
  std::vector<index_t> retval(mpi_size);
  std::fill(retval.begin(), retval.end()-1, ncolEach0() * size);
  retval.back() = ncolEachLast() * size;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a list of the number of rows of the matrix in each MPI node.
///
template<typename _Val>
std::vector<index_t> Parameters<_Val>::rowidxs(
     const index_t size
) const noexcept {
  std::vector<index_t> retval(mpi_size);
  auto count = nrowEach0() * size;
  for ( index_t i = 0; i < mpi_size; ++i ) {
    retval[i] = count * i;
  }
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a list of the number of columns of the matrix in each MPI node.
///
template<typename _Val>
std::vector<index_t> Parameters<_Val>::colidxs(
     const index_t size
) const noexcept {
  std::vector<index_t> retval(mpi_size);
  auto count = ncolEach0() * size;
  for ( index_t i = 0; i < mpi_size; ++i ) {
    retval[i] = count * i;
  }
  return retval;
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
/// @brief  Gets the number of random sketches of all MPI nodes.
///
template<typename _Val>
index_t Parameters<_Val>::numSketch() const noexcept {
  return params_.num_sketch_each_ * mpi_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of random sketches per MPI node.
///
template<typename _Val>
index_t Parameters<_Val>::numSketchEach() const noexcept {
  return params_.num_sketch_each_;
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
/// @attention  @a num_sketch must be a multiple of @ref mcnla::mpi::commSize "mpi_size".
///
template<typename _Val>
Parameters<_Val>& Parameters<_Val>::setNumSketch(
    const index_t num_sketch
) noexcept {
  params_.num_sketch_each_ = num_sketch / mpi_rank;
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
  params_.num_sketch_each_ = num_sketch_each;
  synchronized_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix collection Q.
///
template<typename _Val>
DenseMatrixCollection120<_Val> Parameters<_Val>::createCollectionQ() const noexcept {
  return DenseMatrixCollection120<_Val>(nrow(), dimSketch(), numSketchEach());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixCollection120<_Val> Parameters<_Val>::createCollectionQj() const noexcept {
  return DenseMatrixCollection120<_Val>(nrowEach(), dimSketch(), numSketch());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Q.
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixQ() const noexcept {
  return DenseMatrixRowMajor<_Val>(nrow(), dimSketch());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Creates matrix Qj (j-th row-block, where j is the MPI rank).
///
template<typename _Val>
DenseMatrixRowMajor<_Val> Parameters<_Val>::createMatrixQj() const noexcept {
  return DenseMatrixRowMajor<_Val>(nrowEach(), dimSketch());
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CORE_PARAMETERS_HPP_
