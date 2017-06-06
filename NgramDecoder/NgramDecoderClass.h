#ifndef HOCRF_NGRAM_DECODER_NGRAM_DECODER_CLASS_H_
#define HOCRF_NGRAM_DECODER_NGRAM_DECODER_CLASS_H_

#include <memory>
#include <string>
#include <vector>

#include "../kenlm/lm/model.hh"

namespace NgramDecoder {

struct Word {
    const size_t beginPos;
    const size_t length;
    const std::string ngramString;
    void *data;
    Word(size_t beginPos, size_t length, const std::string ngramString, void *data) : beginPos(beginPos), length(length), ngramString(ngramString), data(data) {};
};

class NgramDecoderClass {
public:
    NgramDecoderClass(const std::string &modelFilename);
    std::vector<size_t> decode(std::vector<Word> &words) const;
    void decode_and_return_lengths(const std::vector<Word> &words, std::vector<size_t> *ret, std::vector<size_t> *orders) const;
private:
    std::shared_ptr<lm::ngram::Model> model;
};

}  // namespace NgramDecoder

#endif  // HOCRF_NGRAM_DECODER_NGRAM_DECODER_CLASS_H_
