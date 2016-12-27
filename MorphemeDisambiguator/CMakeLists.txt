add_executable(
    MorphemeDisambiguatorMain
    MorphemeDisambiguatorMain.cpp
)

add_library(
    MorphemeDisambiguator
    MorphemeDisambiguatorClass.cpp
)

set_property(TARGET MorphemeDisambiguator PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeDisambiguator Dictionary MaxEnt)
target_link_libraries(MorphemeDisambiguatorMain MorphemeDisambiguator)
