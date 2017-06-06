add_library(
    KoreanAnalyzer
    SHARED
    KoreanAnalyzerClass.cpp
    KoreanConcatenatorClass.cpp
)

add_library(
    KoreanAnalyzerLib
    KoreanAnalyzerClass.cpp
    KoreanConcatenatorClass.cpp
)

add_executable(
    KoreanAnalyzerMain
    KoreanAnalyzerMain.cpp
)

add_executable(
    KoreanConcatenatorMain
    KoreanConcatenatorMain.cpp
)

set_property(TARGET KoreanAnalyzer PROPERTY CXX_STANDARD 11)
set_property(TARGET KoreanAnalyzerLib PROPERTY CXX_STANDARD 11)
set_property(TARGET KoreanAnalyzerMain PROPERTY CXX_STANDARD 11)
target_link_libraries(KoreanAnalyzer DataConverter HighOrderCRF NgramDecoder)
target_link_libraries(KoreanAnalyzerLib DataConverter HighOrderCRF NgramDecoder)
target_link_libraries(KoreanAnalyzerMain KoreanAnalyzerLib)
target_link_libraries(KoreanConcatenatorMain KoreanAnalyzerLib)
