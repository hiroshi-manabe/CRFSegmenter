add_library(
    NgramDecoder
    NgramDecoderClass.cpp
    NgramDictionaryDecoder.cpp
)

set_property(TARGET NgramDecoder PROPERTY CXX_STANDARD 11)
target_link_libraries(NgramDecoder Dictionary kenlm)
target_include_directories(NgramDecoder PUBLIC ../kenlm/)
