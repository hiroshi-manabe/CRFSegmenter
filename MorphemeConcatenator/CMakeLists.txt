add_library(
    MorphemeConcatenator
    MorphemeConcatenatorClass.cpp
)

add_executable(
    MorphemeConcatenatorMain
    MorphemeConcatenatorMain.cpp
)

set_property(TARGET MorphemeConcatenator PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeConcatenator Dictionary Utility)
target_link_libraries(MorphemeConcatenatorMain MorphemeConcatenator)
