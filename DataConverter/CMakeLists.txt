add_executable(
    DataConverterMain
    DataConverterMain.cpp
)

add_library(
    DataConverter
    CharacterFeatureGenerator.cpp
    CharacterTypeFeatureGenerator.cpp
    CharWithSpace.cpp
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
set_property(TARGET DataConverterMain PROPERTY CXX_STANDARD 11)
target_link_libraries(DataConverter Dictionary HighOrderCRF Utility)
target_link_libraries(DataConverterMain DataConverter)
