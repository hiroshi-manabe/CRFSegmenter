add_library(
    Dictionary
    DictionaryClass.cpp
    SingleDictionary.cpp
)
set_property(TARGET Dictionary PROPERTY CXX_STANDARD 11)

target_link_libraries(Dictionary libmarisa Utility)
