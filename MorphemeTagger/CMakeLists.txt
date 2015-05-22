add_executable(
    MorphemeTagger
    MorphemeTaggerClass.cpp
)
set_property(TARGET MorphemeTagger PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeTagger Dictionary)
target_link_libraries(MorphemeTagger MaxEnt)
