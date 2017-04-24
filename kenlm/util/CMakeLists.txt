set(KENLM_UTIL_SOURCE
    bit_packing.cc
    ersatz_progress.cc
    exception.cc
    file.cc
    file_piece.cc
    float_to_string.cc
    integer_to_string.cc
    mmap.cc
    murmur_hash.cc
    parallel_read.cc
    pool.cc
    read_compressed.cc
    scoped.cc
    spaces.cc
    string_piece.cc
    usage.cc
  )

add_subdirectory(double-conversion)

add_library(kenlm_util ${KENLM_UTIL_DOUBLECONVERSION_SOURCE} ${KENLM_UTIL_SOURCE})
