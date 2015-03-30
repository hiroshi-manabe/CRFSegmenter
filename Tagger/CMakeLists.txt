add_executable(
    Tagger
    DictionaryFeatureGenerator.cpp
    WordFeatureGenerator.cpp
    TaggerClass.cpp
)
set_property(TARGET Tagger PROPERTY CXX_STANDARD 11)
target_link_libraries(Tagger HighOrderCRF)
target_link_libraries(Tagger Dictionary)
