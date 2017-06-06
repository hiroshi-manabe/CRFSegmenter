#ifndef HOCRF_NGRAM_DECODER_NGRAM_DICTIONARY_DECODER_H_
#define HOCRF_NGRAM_DECODER_NGRAM_DICTIONARY_DECODER_H_

#include "../Dictionary/DictionaryClass.h"
#include "NgramDecoderClass.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace NgramDecoder {

class NgramDictionaryDecoder {
public:
    NgramDictionaryDecoder(const std::string &model, const std::unordered_set<std::string> &dictionaries);
    std::vector<std::string> decode(const std::vector<std::string> &input) const;
    void decode_and_return_lengths(const std::vector<std::string> &words, std::vector<std::string> *ret, std::vector<size_t> *lengths) const;
private:
    std::shared_ptr<NgramDecoderClass> ngramDecoder;
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
};

}  // namespace NgramDecoder

#endif  // HOCRF_NGRAM_DECODER_NGRAM_DICTIONARY_DECODER_H_
