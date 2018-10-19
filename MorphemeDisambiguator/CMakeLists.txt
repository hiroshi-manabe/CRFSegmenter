add_library(
    MorphemeDisambiguator
    MorphemeDisambiguatorClass.cpp
)

add_executable(
    MorphemeDisambiguatorMain
    MorphemeDisambiguatorMain.cpp
)

set_property(TARGET MorphemeDisambiguator PROPERTY CXX_STANDARD 11)
set_property(TARGET MorphemeDisambiguatorMain PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeDisambiguator Dictionary MaxEnt Utility)
target_link_libraries(MorphemeDisambiguatorMain MorphemeDisambiguator)
