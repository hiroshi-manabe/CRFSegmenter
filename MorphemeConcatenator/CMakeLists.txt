add_library(
    MorphemeConcatenator
    MorphemeConcatenatorClass.cpp
)

set_property(TARGET MorphemeConcatenator PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeConcatenator Dictionary Utility)
