#include <string>

#include "CharWithSpace.h"

#include "UnicodeCharacter.h"

namespace DataConverter {

using std::string;

CharWithSpace::CharWithSpace(UnicodeCharacter c, bool hasSpace)
{
    ch = c;
    sp = hasSpace;
}

const UnicodeCharacter &CharWithSpace::getUnicodeCharacter() const {
    return ch;
}

bool CharWithSpace::hasSpace() const {
    return sp;
}

string CharWithSpace::toString() const {
    string ret = sp ? " " : "";
    return ret + ch.toString();
}

}  // namespace DataConverter
