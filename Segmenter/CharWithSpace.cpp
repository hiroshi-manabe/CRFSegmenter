#include "CharWithSpace.h"

#include "UnicodeCharacter.h"

#include <string>

namespace Segmenter {

using std::string;

CharWithSpace::CharWithSpace(UnicodeCharacter c, bool hasSpace)
{
    ch = c;
    sp = hasSpace;
}

const UnicodeCharacter &CharWithSpace::getUnicodeCharacter() {
    return ch;
}

bool CharWithSpace::hasSpace() {
    return sp;
}

string CharWithSpace::toString() {
    string ret = sp ? " " : "";
    return ret + ch.toString();
}

}  // namespace Segmenter
