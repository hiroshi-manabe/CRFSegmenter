add_library(
    JapaneseAnalyzer
    SHARED
    JapaneseAnalyzer.cpp
    JapaneseAnalyzerProxy.cpp
)

add_library(
    JapaneseAnalyzerLib
    JapaneseAnalyzer.cpp
)

add_executable(
    JapaneseAnalyzerMain
    JapaneseAnalyzerMain.cpp
)

set_property(TARGET JapaneseAnalyzer PROPERTY CXX_STANDARD 11)
set_property(TARGET JapaneseAnalyzerLib PROPERTY CXX_STANDARD 11)
set_property(TARGET JapaneseAnalyzerMain PROPERTY CXX_STANDARD 11)
target_link_libraries(JapaneseAnalyzer DataConverter HighOrderCRF MorphemeDisambiguator)
target_link_libraries(JapaneseAnalyzerLib DataConverter HighOrderCRF MorphemeDisambiguator)
target_link_libraries(JapaneseAnalyzerMain JapaneseAnalyzerLib)
