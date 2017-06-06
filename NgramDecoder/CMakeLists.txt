add_library(
    NgramDecoder
    NgramDecoderClass.cpp
    NgramDictionaryDecoder.cpp
)

add_executable(
    NgramDictionaryDecoderMain
    NgramDictionaryDecoderMain.cpp
)

add_executable(
    NgramSpaceDecoderMain
    NgramSpaceDecoderMain.cpp
)

set_property(TARGET NgramDecoder PROPERTY CXX_STANDARD 11)
set_property(TARGET NgramDictionaryDecoderMain PROPERTY CXX_STANDARD 11)
set_property(TARGET NgramSpaceDecoderMain PROPERTY CXX_STANDARD 11)
target_link_libraries(NgramDecoder Dictionary kenlm)
target_link_libraries(NgramDictionaryDecoderMain NgramDecoder)
target_link_libraries(NgramSpaceDecoderMain NgramDecoder)
target_include_directories(NgramDecoder PUBLIC ../kenlm/)
