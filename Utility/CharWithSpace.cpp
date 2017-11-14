#include "CharWithSpace.h"

#include "CharacterCluster.h"

#include <string>
#include <vector>

namespace Utility {

using std::string;
using std::vector;

using Utility::CharacterCluster;

CharWithSpace::CharWithSpace(CharacterCluster c, bool hasSpace)
{
    ch = c;
    sp = hasSpace;
}

const CharacterCluster &CharWithSpace::getCharacterCluster() const {
    return ch;
}

bool CharWithSpace::hasSpace() const {
    return sp;
}

string CharWithSpace::toString() const {
    string ret = sp ? " " : "";
    return ret + ch.toString();
}

}  // namespace Utility
