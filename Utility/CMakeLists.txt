add_library(
    Utility
    EncryptionUtil.cpp
    FileUtil.cpp
    StringUtil.cpp
    UnicodeCharacter.cpp
)

set_property(TARGET Utility PROPERTY CXX_STANDARD 11)
