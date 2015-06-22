#ifndef HOCRF_HIGH_ORDER_CRF_LABEL_SEQUENCE_H_

#define HOCRF_HIGH_ORDER_CRF_LABEL_SEQUENCE_H_

#include "types.h"

#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

class LabelSequence
{
public:
    LabelSequence() {};
    LabelSequence(vector<label_t> labels);
    size_t getLength() const;
    label_t getLabelAt(size_t pos) const;
    const label_t *getLabelData() const;
    label_t getLastLabel() const;
    LabelSequence createPrefix() const;
    size_t getDifferencePosition(const LabelSequence &that) const;
    static LabelSequence createEmptyLabelSequence();
    bool operator<(const LabelSequence &that) const;
    bool operator==(const LabelSequence &that) const;
    size_t hash() const;

private:
    vector<label_t> labels;
};

}  // namespace HighOrderCRF

namespace std {

template<> 
struct hash<shared_ptr<HighOrderCRF::LabelSequence>> {
    size_t operator()(const shared_ptr<HighOrderCRF::LabelSequence> &seq) const {
        return seq->hash();
    }
};

template<>
struct equal_to<shared_ptr<HighOrderCRF::LabelSequence>> {
    bool operator()(const shared_ptr<HighOrderCRF::LabelSequence>& left, const shared_ptr<HighOrderCRF::LabelSequence> &right) const {
        return *left == *right;
    }
};

}  // namespace std

#endif  // HOCRF_HIGH_ORDER_CRF_LABEL_SEQUENCE_H
