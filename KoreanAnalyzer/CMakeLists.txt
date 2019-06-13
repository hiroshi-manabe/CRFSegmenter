add_library(
    KoreanAnalyzer
    KoreanAnalyzerClass.cpp
    KoreanConcatenatorClass.cpp
)
set_property(TARGET KoreanAnalyzer PROPERTY CXX_STANDARD 11)
target_link_libraries(KoreanAnalyzer DataConverter HighOrderCRF NgramDecoder)
