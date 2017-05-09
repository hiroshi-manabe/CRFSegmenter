#ifndef HOCRF_UTILITY_UNICODE_CHARACTER_H
#define HOCRF_UTILITY_UNICODE_CHARACTER_H

#include <cstdint>
#include <string>
#include <vector>

namespace Utility {

class UnicodeCharacter {
public:
    UnicodeCharacter();
    ~UnicodeCharacter();
    UnicodeCharacter(const UnicodeCharacter &uchar);
    UnicodeCharacter(uint32_t codePoint);
    std::string toString() const;
    uint32_t getCodePoint() const;
    std::string getCharacterType() const;
    static UnicodeCharacter fromString(std::string::const_iterator it, size_t len, size_t *charCount);
    static std::string unicodeCharacterListToString(const std::vector<UnicodeCharacter> &origChars);
    static std::vector<UnicodeCharacter> stringToUnicodeCharacterList(const std::string &orig);
private:
    uint32_t codePoint;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_UNICODE_CHARACTER_H
