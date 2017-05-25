////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/streams/streams.hpp
/// @brief   The random generator driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_STREAMS_STREAMS_HPP_
#define MCNLA_CORE_RANDOM_STREAMS_STREAMS_HPP_

#include <mcnla/core/random/streams/streams.hh>
#include <random>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The random namespace
//
namespace random {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given seed.
/// @copydoc  setSeedImpl
///
Streams::Streams(
    const index_t seed
) noexcept
#ifdef MCNLA_USE_OMP
  : omp_size_(omp_get_max_threads()),
#else  // MCNLA_USE_OMP
  : omp_size_(1),
#endif  // MCNLA_USE_OMP
    streams_(omp_size_) {
  setSeedImpl(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given seed.
/// @copydoc  setSeedsImpl
///
Streams::Streams(
    const index_t seed,
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) noexcept
#ifdef MCNLA_USE_OMP
  : omp_size_(omp_get_max_threads()),
#else  // MCNLA_USE_OMP
  : omp_size_(1),
#endif  // MCNLA_USE_OMP
    streams_(omp_size_) {
  setSeedsImpl(seed, mpi_root, mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
Streams::~Streams() noexcept {
#ifdef MCNLA_USE_MKL
  for ( index_t i = 0; i < omp_size_; ++i ) {
    vslDeleteStream(&(streams_[i]));
  }
#endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of OpenMP threads.
///
index_t Streams::ompSize() const noexcept {
  return omp_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw random stream.
///
Streams::StreamType& Streams::operator[](
    const index_t i
) const noexcept {
  return const_cast<StreamType&>(streams_[i]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
void Streams::setSeed(
    const index_t seed
) noexcept {
#ifdef MCNLA_USE_MKL
  for ( index_t i = 0; i < omp_size_; ++i ) {
    vslDeleteStream(&(streams_[i]));
  }
#endif  // MCNLA_USE_MKL
  setSeedImpl(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generate the random seeds and send to each MPI nodes.
///
void Streams::setSeeds(
    const index_t seed,
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) noexcept {
#ifdef MCNLA_USE_MKL
  for ( index_t i = 0; i < omp_size_; ++i ) {
    vslDeleteStream(&(streams_[i]));
  }
#endif  // MCNLA_USE_MKL
  setSeedsImpl(seed, mpi_root, mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSeed
///
void Streams::setSeedImpl(
    const index_t seed
) noexcept {
  std::seed_seq seq{seed};
  std::vector<index_t> seeds(omp_size_);
  seq.generate(seeds.begin(), seeds.end());
  for ( index_t i = 0; i < omp_size_; ++i ) {
#ifdef MCNLA_USE_MKL
    vslNewStream(&(streams_[i]), VSL_BRNG_SFMT19937, seeds[i]);
#else  // MCNLA_USE_MKL
    streams_[i].seed(seeds[i]);
#endif  // MCNLA_USE_MKL
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSeeds
///
void Streams::setSeedsImpl(
    const index_t seed,
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) noexcept {
  std::vector<index_t> seeds(mpi::commSize(mpi_comm));
  if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
    std::seed_seq seq{seed};
    seq.generate(seeds.begin(), seeds.end());
  }
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp;
  MPI_Scatter(seeds.data(), 1, datatype, &seed_tmp, 1, datatype, mpi_root, mpi_comm);
  setSeedImpl(seed_tmp);
}

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_STREAMS_STREAMS_HPP_
