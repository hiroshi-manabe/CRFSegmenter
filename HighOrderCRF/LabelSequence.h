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
struct less<std::shared_ptr<HighOrderCRF::LabelSequence>> {
    bool operator()(const std::shared_ptr<HighOrderCRF::LabelSequence>& left, const std::shared_ptr<HighOrderCRF::LabelSequence> &right) const {
        return *left < *right;
    }
};

}

#endif  // HOCRF_HIGH_ORDER_CRF_LABEL_SEQUENCE_H
