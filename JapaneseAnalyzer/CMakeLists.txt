add_library(
    JapaneseAnalyzer
    JapaneseAnalyzerClass.cpp
)
set_property(TARGET JapaneseAnalyzer PROPERTY CXX_STANDARD 11)
target_link_libraries(JapaneseAnalyzer DataConverter HighOrderCRF MorphemeDisambiguator MorphemeConcatenator)
