#ifndef HOCRF_DATA_CONVERTER_UNICODE_CHARACTER_H
#define HOCRF_DATA_CONVERTER_UNICODE_CHARACTER_H

#include <cstdint>
#include <string>

namespace DataConverter {

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
private:
    uint32_t codePoint;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_UNICODE_CHARACTER_H
