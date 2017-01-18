#include "CharWithSpace.h"

#include "../Utility/UnicodeCharacter.h"

#include <string>

namespace DataConverter {

using std::string;
using Utility::UnicodeCharacter;

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
