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
    UnicodeCharacter(std::string::const_iterator beginIterator, std::string::const_iterator endIterator, size_t *charCount);
    std::string toString() const;
    uint32_t getCodePoint() const;
    std::string getCharacterType() const;
    static std::string unicodeCharacterListToString(const std::vector<UnicodeCharacter> &origChars);
    static std::vector<UnicodeCharacter> stringToUnicodeCharacterList(const std::string &orig);
private:
    uint32_t codePoint;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_UNICODE_CHARACTER_H
