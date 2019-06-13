cmake_minimum_required (VERSION 2.6)
project (HOCRF)

if (NOT MSVC)
    list(APPEND CMAKE_CXX_FLAGS "-pthread -fPIC ${CMAKE_CXX_FLAGS}")
    list(APPEND CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(kenlm)
add_subdirectory(liblbfgs)
add_subdirectory(libmarisa)
add_subdirectory(DataConverter)
add_subdirectory(Dictionary)
add_subdirectory(HighOrderCRF)
add_subdirectory(JapaneseAnalyzer)
add_subdirectory(KoreanAnalyzer)
add_subdirectory(MaxEnt)
add_subdirectory(MorphemeConcatenator)
add_subdirectory(MorphemeDisambiguator)
add_subdirectory(NgramDecoder)
add_subdirectory(Optimizer)
add_subdirectory(Utility)
add_dependencies(Optimizer liblbfgs)
add_dependencies(HighOrderCRF Optimizer Utility)
add_dependencies(MaxEnt Optimizer)
add_dependencies(Dictionary libmarisa Utility)
add_dependencies(DataConverter Dictionary HighOrderCRF Utility)
add_dependencies(MorphemeConcatenator Dictionary Utility)
add_dependencies(MorphemeDisambiguator Dictionary MaxEnt Utility)
add_dependencies(JapaneseAnalyzer DataConverter HighOrderCRF MorphemeConcatenator MorphemeDisambiguator)
add_dependencies(NgramDecoder kenlm)
add_dependencies(KoreanAnalyzer DataConverter HighOrderCRF NgramDecoder)

add_executable(
    KoreanAnalyzerMain
    KoreanAnalyzer/KoreanAnalyzerMain.cpp
)
set_property(TARGET KoreanAnalyzerMain PROPERTY CXX_STANDARD 11)
target_link_libraries(KoreanAnalyzerMain KoreanAnalyzer)

add_executable(
    KoreanConcatenatorMain
    KoreanAnalyzer/KoreanConcatenatorMain.cpp
)
set_property(TARGET KoreanConcatenatorMain PROPERTY CXX_STANDARD 11)
target_link_libraries(KoreanConcatenatorMain KoreanAnalyzer)

add_executable(
    DataConverterMain
    DataConverter/DataConverterMain.cpp
)
set_property(TARGET DataConverterMain PROPERTY CXX_STANDARD 11)
target_link_libraries(DataConverterMain DataConverter)

add_executable(
    DictionaryMain
    Dictionary/DictionaryMain.cpp
)
set_property(TARGET DictionaryMain PROPERTY CXX_STANDARD 11)
target_link_libraries(DictionaryMain Dictionary)

add_executable(
    HighOrderCRFMain
    HighOrderCRF/HighOrderCRFMain.cpp
)
set_property(TARGET HighOrderCRFMain PROPERTY CXX_STANDARD 11)
target_link_libraries(HighOrderCRFMain HighOrderCRF)

add_executable(
    MorphemeDisambiguatorMain
    MorphemeDisambiguator/MorphemeDisambiguatorMain.cpp
)
set_property(TARGET MorphemeDisambiguatorMain PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeDisambiguatorMain MorphemeDisambiguator)

add_executable(
    NgramDictionaryDecoderMain
    NgramDecoder/NgramDictionaryDecoderMain.cpp
)
set_property(TARGET NgramDictionaryDecoderMain PROPERTY CXX_STANDARD 11)
target_link_libraries(NgramDictionaryDecoderMain NgramDecoder)

add_executable(
    NgramSpaceDecoderMain
    NgramDecoder/NgramSpaceDecoderMain.cpp
)
set_property(TARGET NgramSpaceDecoderMain PROPERTY CXX_STANDARD 11)
target_link_libraries(NgramSpaceDecoderMain NgramDecoder)

add_executable(
    JapaneseAnalyzerMain
    JapaneseAnalyzer/JapaneseAnalyzerMain.cpp
)
set_property(TARGET JapaneseAnalyzerMain PROPERTY CXX_STANDARD 11)
target_link_libraries(JapaneseAnalyzerMain JapaneseAnalyzer)

add_executable(
    MorphemeConcatenatorMain
    MorphemeConcatenator/MorphemeConcatenatorMain.cpp
)
set_property(TARGET MorphemeConcatenatorMain PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeConcatenatorMain MorphemeConcatenator)

install(TARGETS KoreanAnalyzerMain KoreanConcatenatorMain DataConverterMain HighOrderCRFMain MorphemeDisambiguatorMain NgramDictionaryDecoderMain NgramSpaceDecoderMain JapaneseAnalyzerMain MorphemeConcatenatorMain DESTINATION bin)
