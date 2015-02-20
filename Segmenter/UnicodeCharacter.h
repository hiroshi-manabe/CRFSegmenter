#ifndef SEGMENTER_UNICODE_CHARACTER_H
#define SEGMENTER_UNICODE_CHARACTER_H

#include <cstdint>
#include <string>

namespace Segmenter {

using std::string;

class UnicodeCharacter {
public:
    UnicodeCharacter();
    ~UnicodeCharacter();
    UnicodeCharacter(const UnicodeCharacter &uchar);
    UnicodeCharacter(uint32_t codePoint);
    string toString() const;
    uint32_t getCodePoint() const;
    string getCharacterType() const;
    static UnicodeCharacter fromString(const char *buf, size_t len, size_t *charCount);
private:
    uint32_t codePoint;
};

}

#endif  // SEGMENTER_UNICODE_CHARACTER_H
