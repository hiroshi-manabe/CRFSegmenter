add_executable(
    Segmenter
    CharacterFeatureGenerator.cpp
    CharacterTypeFeatureGenerator.cpp
    SegmenterClass.cpp
    UnicodeCharacter.cpp
)
set_property(TARGET Segmenter PROPERTY CXX_STANDARD 11)
target_link_libraries(Segmenter HighOrderCRF)
