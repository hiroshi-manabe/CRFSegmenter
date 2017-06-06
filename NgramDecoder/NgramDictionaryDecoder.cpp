#include "NgramDictionaryDecoder.h"
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

NgramDictionaryDecoder::NgramDictionaryDecoder(const string &modelFilename, const unordered_set<string> &dictionaries) {
    dictionary = make_shared<DictionaryClass>(dictionaries);
    ngramDecoder = make_shared<NgramDecoderClass>(modelFilename);
}

void NgramDictionaryDecoder::decode_and_return_lengths(const vector<string> &input, vector<string> *ret, vector<size_t> *lengths) const {
    ret->clear();
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
    vector<size_t> indexes;
    ngramDecoder->decode_and_return_lengths(words, &indexes, lengths);
    for (const auto index : indexes) {
        ret->emplace_back(words[index].ngramString);
    }
}

vector<string> NgramDictionaryDecoder::decode(const vector<string> &input) const {
    vector<string> ret;
    vector<size_t> lengths;
    decode_and_return_lengths(input, &ret, &lengths);
    return ret;
}

}  // namespace NgramDecoder
