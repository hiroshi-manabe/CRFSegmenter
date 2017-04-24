# Explicitly list the source files for this subdirectory
#
# If you add any source files to this subdirectory
#    that should be included in the kenlm library,
#        (this excludes any unit test files)
#    you should add them to the following list:
set(KENLM_LM_SOURCE
    bhiksha.cc
    binary_format.cc
    config.cc
    lm_exception.cc
    model.cc
    quantize.cc
    read_arpa.cc
    search_hashed.cc
    search_trie.cc
    sizes.cc
    trie.cc
    trie_sort.cc
    value_build.cc
    virtual_interface.cc
    vocab.cc
)

if (NOT MSVC)
	set(THREADS pthread)
endif()

add_library(kenlm ${KENLM_LM_SOURCE})
target_link_libraries(kenlm kenlm_util ${THREADS})

set(KENLM_MAX_ORDER 6 CACHE STRING "Maximum supported ngram order")
target_compile_definitions(kenlm PUBLIC -DKENLM_MAX_ORDER=${KENLM_MAX_ORDER})

