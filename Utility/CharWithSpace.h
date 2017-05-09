#ifndef HOCRF_UTILITY_CHAR_WITH_SPACE_H
#define HOCRF_UTILITY_CHAR_WITH_SPACE_H

#include "UnicodeCharacter.h"

#include <string>

namespace Utility {

class CharWithSpace {
public:
    CharWithSpace(Utility::UnicodeCharacter c, bool hasSpace);
    const Utility::UnicodeCharacter &getUnicodeCharacter() const;
    bool hasSpace() const;
    std::string toString() const;
    static std::string charWithSpaceListToString(const std::vector<CharWithSpace> &origChars);
    static std::vector<CharWithSpace> stringToCharWithSpaceList(const std::string &orig);

private:
    Utility::UnicodeCharacter ch;
    bool sp;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_CHAR_WITH_SPACE_H
