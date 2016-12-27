add_library(
    MaxEnt
    CompiledData.cpp
    MaxEntData.cpp
    MaxEntProcessor.cpp
    Observation.cpp
)
set_property(TARGET MaxEnt PROPERTY CXX_STANDARD 11)
target_link_libraries(MaxEnt Optimizer)
