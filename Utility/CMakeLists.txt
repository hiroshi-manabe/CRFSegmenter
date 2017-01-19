add_library(
    Utility
    FileUtil.cpp
    StringUtil.cpp
    UnicodeCharacter.cpp
)

set_property(TARGET Utility PROPERTY CXX_STANDARD 11)
