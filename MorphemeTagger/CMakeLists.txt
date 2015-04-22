add_executable(
    MorphemeTagger
    MorphemeTaggerClass.cpp
    Dictionary.cpp
)
set_property(TARGET MorphemeTagger PROPERTY CXX_STANDARD 11)
target_link_libraries(MorphemeTagger MaxEnt)
