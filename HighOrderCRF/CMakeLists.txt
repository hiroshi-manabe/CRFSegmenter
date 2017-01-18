add_executable(
    HighOrderCRFMain
    HighOrderCRFMain.cpp
)

add_library(
    HighOrderCRF
    DataSequence.cpp
    Feature.cpp
    FeatureTemplate.cpp
    HighOrderCRFData.cpp
    HighOrderCRFProcessor.cpp
    InternalDataSequence.cpp
    LabelSequence.cpp
    PatternSetSequence.cpp
)

set_property(TARGET HighOrderCRF PROPERTY CXX_STANDARD 11)
set_property(TARGET HighOrderCRFMain PROPERTY CXX_STANDARD 11)

target_link_libraries(HighOrderCRF Optimizer Utility)
target_link_libraries(HighOrderCRFMain HighOrderCRF)
