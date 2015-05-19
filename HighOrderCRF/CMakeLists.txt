add_library(
    HighOrderCRF
    CompactPatternSetSequence.cpp
    DataSequence.cpp
    Feature.cpp
    FeatureTemplate.cpp
    HighOrderCRFData.cpp
    LabelSequence.cpp
)
set_property(TARGET HighOrderCRF PROPERTY CXX_STANDARD 11)
target_link_libraries(HighOrderCRF Optimizer)
