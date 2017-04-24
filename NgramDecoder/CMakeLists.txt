add_library(
    NgramDecoder
    NgramDecoderClass.cpp
    DictionaryDecoder.cpp
)

add_executable(
    DictionaryDecoderMain
    DictionaryDecoderMain.cpp
)

set_property(TARGET NgramDecoder PROPERTY CXX_STANDARD 11)
set_property(TARGET DictionaryDecoderMain PROPERTY CXX_STANDARD 11)
target_link_libraries(NgramDecoder Dictionary kenlm)
target_link_libraries(DictionaryDecoderMain NgramDecoder)
target_include_directories(NgramDecoder PUBLIC ../kenlm/)
