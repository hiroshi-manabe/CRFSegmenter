#include "DictionaryDecoder.h"
#include "NgramDecoderClass.h"

#include "../Dictionary/DictionaryClass.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using std::make_shared;
using std::string;
using std::unordered_set;
using std::vector;

using Dictionary::DictionaryClass;

namespace NgramDecoder {

DictionaryDecoder::DictionaryDecoder(const string &modelFilename, const unordered_set<string> &dictionaries) {
    dictionary = make_shared<DictionaryClass>(dictionaries);
    ngramDecoder = make_shared<NgramDecoderClass>(modelFilename);
}

vector<string> DictionaryDecoder::decode(const vector<string> &input) const {
    vector<Word> words;
    size_t pos = 0;
    for (const auto &str : input) {
        auto vv = dictionary->lookup(str);
        for (const auto v : vv) {
            words.emplace_back(Word{ pos, 1, v[0], nullptr });
        }
        if (vv.empty()) {
            words.emplace_back(Word{ pos, 1, str, nullptr });
        }
        pos++;
    }
    auto decoded = ngramDecoder->decode(words);
    vector<string> ret;
    for (const auto word : decoded) {
        ret.emplace_back(word->ngramString);
    }
    return ret;
}

}  // namespace NgramDecoder
