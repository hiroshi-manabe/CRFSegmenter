#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "CharacterCluster.h"

namespace Utility {

using std::string;
using std::vector;

CharacterCluster::CharacterCluster() {
}

CharacterCluster::~CharacterCluster() {
}

CharacterCluster::CharacterCluster(const vector<UnicodeCharacter> &chars) {
    characters = chars;
}

CharacterCluster::CharacterCluster(const CharacterCluster &other) {
    characters = other.characters;
}

CharacterCluster::CharacterCluster(string::const_iterator beginIterator, string::const_iterator endIterator) {
    characters.clear();
    while (beginIterator < endIterator) {
        size_t s;
        characters.emplace_back(beginIterator, endIterator, &s);
        beginIterator += s;
    }
}

string CharacterCluster::toString() const {
    string ret;
    for (const auto &c : characters) {
        ret += c.toString();
    }
    return ret;
}

string CharacterCluster::getFirstCharacterType() const {
    return characters[0].getCharacterType();
}

uint32_t CharacterCluster::getFirstCodePoint() const {
    return characters[0].getCodePoint();
}

}  // namespace Utility
