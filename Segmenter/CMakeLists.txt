add_executable(
    Segmenter
    CharacterFeatureGenerator.cpp
    CharacterTypeFeatureGenerator.cpp
    CharWithSpace.cpp
    CharWithSpaceFeatureGenerator.cpp
    CharWithSpaceTypeFeatureGenerator.cpp
    DictionaryFeatureGenerator.cpp
    SegmenterClass.cpp
    UnicodeCharacter.cpp
)
set_property(TARGET Segmenter PROPERTY CXX_STANDARD 11)
target_link_libraries(Segmenter HighOrderCRF)
target_link_libraries(Segmenter Dictionary)
