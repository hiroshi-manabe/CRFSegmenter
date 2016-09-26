#ifndef HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H
#define HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H

#include "UnicodeCharacter.h"
#include <string>

namespace DataConverter {

class CharWithSpace {
public:
    CharWithSpace(UnicodeCharacter c, bool hasSpace);
    const UnicodeCharacter &getUnicodeCharacter() const;
    bool hasSpace() const;
    std::string toString() const;

private:
    UnicodeCharacter ch;
    bool sp;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H
