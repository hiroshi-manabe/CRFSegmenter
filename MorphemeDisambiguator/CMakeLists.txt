add_executable(
    MorphemeDisambiguator
    MorphemeDisambiguatorMain.cpp
)
set_property(TARGET MorphemeDisambiguator PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeDisambiguator Dictionary)
target_link_libraries(MorphemeDisambiguator MaxEnt)
