#ifndef HOCRF_UTILITY_CHAR_WITH_SPACE_H
#define HOCRF_UTILITY_CHAR_WITH_SPACE_H

#include "CharacterCluster.h"

#include <string>

namespace Utility {

class CharWithSpace {
public:
    CharWithSpace(Utility::CharacterCluster c, bool hasSpace);
    const Utility::CharacterCluster &getCharacterCluster() const;
    bool hasSpace() const;
    std::string toString() const;

private:
    Utility::CharacterCluster ch;
    bool sp;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_CHAR_WITH_SPACE_H
