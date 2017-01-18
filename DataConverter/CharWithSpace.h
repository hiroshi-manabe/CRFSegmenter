#ifndef HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H
#define HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H

#include "../Utility/UnicodeCharacter.h"

#include <string>

namespace DataConverter {

class CharWithSpace {
public:
    CharWithSpace(Utility::UnicodeCharacter c, bool hasSpace);
    const Utility::UnicodeCharacter &getUnicodeCharacter() const;
    bool hasSpace() const;
    std::string toString() const;

private:
    Utility::UnicodeCharacter ch;
    bool sp;
};

}  // namespace DataConverter

#endif  // HOCRF_DATA_CONVERTER_CHAR_WITH_SPACE_H
