add_executable(
    DataConverter
    CharacterFeatureGenerator.cpp
    CharacterTypeFeatureGenerator.cpp
    CharWithSpace.cpp
    CharWithSpaceFeatureGenerator.cpp
    CharWithSpaceTypeFeatureGenerator.cpp
    DataConverterMain.cpp
    DictionaryFeatureGenerator.cpp
    SegmenterDataConverter.cpp
    SegmenterDictionaryFeatureGenerator.cpp
    TaggerDataConverter.cpp
    UnicodeCharacter.cpp
    WordCharacterFeatureGenerator.cpp
    WordCharacterTypeFeatureGenerator.cpp
    WordFeatureGenerator.cpp
)
set_property(TARGET DataConverter PROPERTY CXX_STANDARD 11)
target_link_libraries(DataConverter Dictionary)
