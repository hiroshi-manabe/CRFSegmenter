#ifndef HOCRF_LABEL_SEQUENCE_H_
#define HOCRF_LABEL_SEQUENCE_H_

#include "types.h"

#include <memory>
#include <string>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::string;
using std::vector;

class LabelSequence
{
public:
    LabelSequence(shared_ptr<vector<label_t>> labels);
    size_t getLength() const;
    label_t getLabelAt(size_t pos) const;
    label_t getLastLabel() const;
    shared_ptr<LabelSequence> createPrefix() const;
    size_t getDifferencePosition(const shared_ptr<LabelSequence> &that) const;
    static shared_ptr<LabelSequence> createEmptyLabelSequence();
    bool operator<(const LabelSequence &that);
    bool operator==(const LabelSequence &that);
    size_t hash() const;

private:
    shared_ptr<vector<label_t>> labels;
};

}  // namespace HighOrderCRF

namespace std {

template<>
struct hash<std::shared_ptr<HighOrderCRF::LabelSequence>> {
    std::size_t operator()(const std::shared_ptr<HighOrderCRF::LabelSequence> &labelSequence) const {
        return labelSequence->hash();
    }
};

template<>
struct equal_to<std::shared_ptr<HighOrderCRF::LabelSequence>> {
    bool operator()(const std::shared_ptr<HighOrderCRF::LabelSequence>& left, const std::shared_ptr<HighOrderCRF::LabelSequence> &right) const {
        return *left == *right;
    }
};

template<>
struct less<std::shared_ptr<HighOrderCRF::LabelSequence>> {
    bool operator()(const std::shared_ptr<HighOrderCRF::LabelSequence>& left, const std::shared_ptr<HighOrderCRF::LabelSequence> &right) const {
        return *left < *right;
    }
};

}

#endif  // HOCRF_LABEL_SEQUENCE_H
