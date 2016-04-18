#ifndef HOCRF_SEGMENTER_CHAR_WITH_SPACE_H
#define HOCRF_SEGMENTER_CHAR_WITH_SPACE_H

#include "UnicodeCharacter.h"
#include <string>

namespace Segmenter {

class CharWithSpace {
public:
    CharWithSpace(UnicodeCharacter c, bool hasSpace);
    const UnicodeCharacter &getUnicodeCharacter();
    bool hasSpace();
    std::string toString();

private:
    UnicodeCharacter ch;
    bool sp;
};

}

#endif  // HOCRF_SEGMENTER_CHAR_WITH_SPACE_H
