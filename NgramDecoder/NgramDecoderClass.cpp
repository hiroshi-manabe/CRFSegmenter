#include "NgramDecoderClass.h"

#include "../kenlm/lm/model.hh"

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::make_pair;
using std::make_shared;
using std::max;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace std {

template<>
struct hash<lm::ngram::State>
{
    size_t operator()(const lm::ngram::State &state) const {
        return hash_value(state);
    };
};

template<>
struct hash<pair<size_t, lm::WordIndex>>
{
    size_t operator()(const pair<size_t, lm::WordIndex> &p) const {
        return hash<size_t>()(p.first) ^ hash<lm::WordIndex>()(p.second);
    };
};

}

namespace NgramDecoder {

NgramDecoderClass::NgramDecoderClass(const string &modelFilename) {
    model = make_shared<lm::ngram::Model>(modelFilename.c_str());
}

struct Node {
    const size_t wordSubscript;
    shared_ptr<Node> left;
    size_t ngram_length;
    float score;
};

void NgramDecoderClass::decode_and_return_lengths(const vector<Word> &words, vector<size_t> *ret, vector<size_t> *lengths) const {
    ret->clear();
    lengths->clear();

    const lm::ngram::Vocabulary &vocab = model->GetVocabulary();
    unordered_map<size_t, unordered_set<pair<size_t, lm::WordIndex>>> wordsByPositionMap;
    unordered_map<size_t, unordered_map<lm::WordIndex, const Word *>> wordIndexToWordMap;
    size_t maxPosition = 0;
    for (size_t i = 0; i < words.size(); ++i) {
        const auto &word = words[i];
        auto index = vocab.Index(word.ngramString);
        wordsByPositionMap[word.beginPos].emplace(make_pair(i, index));
        maxPosition = max(maxPosition, word.beginPos + word.length);
    }
    wordsByPositionMap[maxPosition].emplace(make_pair(words.size(), vocab.EndSentence()));
    vector<unordered_map<lm::ngram::State, shared_ptr<Node>>> lattice(maxPosition + 2);
    lm::ngram::State beginState = model->BeginSentenceState();
    lattice[0].emplace(beginState, make_shared<Node>(Node{ words.size(), nullptr, 0, 0.0 }));
    for (int position = 0; position <= maxPosition; ++position) {
        for (auto entry : lattice.at(position)) {
            auto &curState = entry.first;
            auto &curNode = entry.second;
            for (const auto pair : wordsByPositionMap[position]) {
                const auto wordSubscript = pair.first;
                size_t length = wordSubscript == words.size() ? 1 : words[wordSubscript].length;
                auto wordIndex = pair.second;
                lm::ngram::State newState;
                lm::FullScoreReturn ret = model->FullScore(curState, wordIndex, newState);
                float score = ret.prob;
                float newScore = curNode->score + score;
                
                auto &rightMap = lattice[position + length];
                auto it = rightMap.find(newState);
                if (it == rightMap.end() || newScore > it->second->score) {
                    rightMap[newState] = make_shared<Node>(Node { wordSubscript, entry.second, ret.ngram_length, newScore });
                }
            }
        }
    }

    if (lattice[maxPosition + 1].size() == 0) {
        return;
    }

    float bestScore = 0.0;
    shared_ptr<Node> bestNode;
    const auto &endMap = lattice[maxPosition + 1];
    for (const auto &entry : endMap) {
        const auto node = entry.second;
        if (!bestNode || node->score > bestScore) {
            bestScore = node->score;
            bestNode = node;
        }
    }
    bestNode = bestNode->left;

    while (bestNode->left) {
        ret->insert(ret->begin(), bestNode->wordSubscript);
        lengths->insert(lengths->begin(), bestNode->ngram_length);
        bestNode = bestNode->left;
    }
    
    return;
}

vector<size_t> NgramDecoderClass::decode(vector<Word> &words) const {
    vector<size_t> indexes;
    vector<size_t> orders;
    decode_and_return_lengths(words, &indexes, &orders);
    
    return indexes;
}

}  // namespace NgramDecoder
