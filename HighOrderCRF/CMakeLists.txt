add_executable(
    HighOrderCRFMain
    HighOrderCRFMain.cpp
)

add_library(
    HighOrderCRF
    PatternSetSequence.cpp
    DataSequence.cpp
    Feature.cpp
    HighOrderCRFData.cpp
    HighOrderCRFProcessor.cpp
    LabelSequence.cpp
)

set_property(TARGET HighOrderCRF PROPERTY CXX_STANDARD 11)
set_property(TARGET HighOrderCRFMain PROPERTY CXX_STANDARD 11)

target_link_libraries(HighOrderCRF Optimizer)
target_link_libraries(HighOrderCRFMain HighOrderCRF)
