add_library(
    Utility
    CharacterCluster.cpp
    CharWithSpace.cpp
    EncryptionUtil.cpp
    FileUtil.cpp
    KoreanUtil.cpp
    SegmenterUtil.cpp
    StringUtil.cpp
    UnicodeCharacter.cpp
)

set_property(TARGET Utility PROPERTY CXX_STANDARD 11)
