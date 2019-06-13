add_library(
    DataConverter
    CharacterFeatureGenerator.cpp
    CharacterTypeFeatureGenerator.cpp
    CharWithSpaceFeatureGenerator.cpp
    CharWithSpaceTypeFeatureGenerator.cpp
    DictionaryFeatureGenerator.cpp
    SegmenterDataConverter.cpp
    SegmenterDictionaryFeatureGenerator.cpp
    TaggerDataConverter.cpp
    WordCharacterFeatureGenerator.cpp
    WordCharacterTypeFeatureGenerator.cpp
    WordFeatureGenerator.cpp
)

set_property(TARGET DataConverter PROPERTY CXX_STANDARD 11)
target_link_libraries(DataConverter Dictionary HighOrderCRF Utility)
