#ifndef HOCRF_NGRAM_DECODER_DICTIONARY_DECODER_H_
#define HOCRF_NGRAM_DECODER_DICTIONARY_DECODER_H_

#include "../Dictionary/DictionaryClass.h"
#include "NgramDecoderClass.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace NgramDecoder {

class DictionaryDecoder {
public:
    DictionaryDecoder(const std::string &model, const std::unordered_set<std::string> &dictionaries);
    std::vector<std::string> decode(const std::vector<std::string> &input) const;
private:
    std::shared_ptr<NgramDecoderClass> ngramDecoder;
    std::shared_ptr<Dictionary::DictionaryClass> dictionary;
};

}  // namespace NgramDecoder

#endif  // HOCRF_NGRAM_DECODER_DICTIONARY_DECODER_H_
