add_library(
    Utility
    CharWithSpace.cpp
    EncryptionUtil.cpp
    FileUtil.cpp
    StringUtil.cpp
    UnicodeCharacter.cpp
)

set_property(TARGET Utility PROPERTY CXX_STANDARD 11)
