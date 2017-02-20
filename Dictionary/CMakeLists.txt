add_library(
    Dictionary
    DictionaryClass.cpp
    SingleDictionary.cpp
)
add_executable(
    DictionaryMain
    DictionaryMain.cpp
)

set_property(TARGET Dictionary PROPERTY CXX_STANDARD 11)
set_property(TARGET DictionaryMain PROPERTY CXX_STANDARD 11)

target_link_libraries(Dictionary libmarisa Utility)
target_link_libraries(DictionaryMain Dictionary)
