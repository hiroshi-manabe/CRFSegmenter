add_executable(
    HighOrderCRF
    PatternSetSequence.cpp
    DataSequence.cpp
    Feature.cpp
    HighOrderCRFData.cpp
    HighOrderCRFMain.cpp
    HighOrderCRFProcessor.cpp
    LabelSequence.cpp
)
set_property(TARGET HighOrderCRF PROPERTY CXX_STANDARD 11)
target_link_libraries(HighOrderCRF Optimizer)
