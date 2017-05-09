#include "CharWithSpace.h"

#include "UnicodeCharacter.h"

#include <string>
#include <vector>

namespace Utility {

using std::string;
using std::vector;

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

vector<CharWithSpace> CharWithSpace::stringToCharWithSpaceList(const string &orig) {
    vector<CharWithSpace> ret;
    for (auto it = orig.begin(); it != orig.end(); ) {
        size_t charCount;
        bool hasSpace = false;
        if (*it == ' ') {
            hasSpace = true;
            it++;
        }
        ret.emplace_back(UnicodeCharacter::fromString(it, orig.end() - it, &charCount), it == orig.begin() || hasSpace);
        it += charCount;
    }
    return ret;
}

string CharWithSpace::charWithSpaceListToString(const vector<CharWithSpace> &origChars) {
    string ret;
    for (const auto c : origChars) {
        ret += c.toString();
    }
    return ret.substr(1);
}


}  // namespace Utility
