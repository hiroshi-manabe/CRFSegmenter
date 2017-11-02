#ifndef HOCRF_UTILITY_CHARACTER_CLUSTER_H
#define HOCRF_UTILITY_CHARACTER_CLUSTER_H

#include "UnicodeCharacter.h"

#include <cstdint>
#include <string>
#include <vector>

namespace Utility {

class CharacterCluster {
public:
    CharacterCluster();
    ~CharacterCluster();
    CharacterCluster(const CharacterCluster &other);
    CharacterCluster(const std::vector<UnicodeCharacter> &chars);
    CharacterCluster(std::string::const_iterator beginIterator, std::string::const_iterator endIterator);
    std::string toString() const;
    uint32_t getFirstCodePoint() const;
    std::string getFirstCharacterType() const;
private:
    std::vector<UnicodeCharacter> characters;
};

}  // namespace Utility

#endif  // HOCRF_UTILITY_CHARACTER_CLUSTER_H
