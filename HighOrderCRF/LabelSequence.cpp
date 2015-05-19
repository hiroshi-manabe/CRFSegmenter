#include "LabelSequence.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::make_shared;
using std::min;
using std::shared_ptr;
using std::vector;

LabelSequence::LabelSequence(shared_ptr<vector<label_t>> labels) {
    this->labels = labels;
}

size_t LabelSequence::getLength() const {
    return labels->size();
}

label_t LabelSequence::getLabelAt(size_t pos) const {
    if (pos >= labels->size()) {
        return INVALID_LABEL;
    }
    return labels->at(pos);
}

label_t *LabelSequence::getLabelData() const {
    return labels->data();
}

label_t LabelSequence::getLastLabel() const {
    return getLabelAt(0);
}

shared_ptr<LabelSequence> LabelSequence::createPrefix() const {
    auto seq = make_shared<vector<label_t>>(labels->begin() + 1, labels->end());
    return make_shared<LabelSequence>(seq);
}

size_t LabelSequence::getDifferencePosition(const shared_ptr<LabelSequence> &that) const {
    size_t minLength = min(getLength(), that->getLength());
    for (size_t i = 0; i < minLength; ++i) {
        if (getLabelAt(i) != that->getLabelAt(i)) {
            return i;
        }
    }
    return minLength;
}

bool LabelSequence::operator<(const LabelSequence &that) {
    size_t thisLength = getLength();
    size_t thatLength = that.getLength();

    size_t minLength = min(thisLength, thatLength);

    for (size_t i = 0; i < minLength; ++i) {
        if (getLabelAt(i) != that.getLabelAt(i)) {
            return getLabelAt(i) < that.getLabelAt(i);
        }
    }
    return thisLength < thatLength;
}

bool LabelSequence::operator==(const LabelSequence &that) {
    if (this->getLength() != that.getLength()) {
        return false;
    }

    for (size_t i = 0; i < this->getLength(); ++i) {
        if (getLabelAt(i) != that.getLabelAt(i)) {
            return false;
        }
    }
    return true;
}


size_t LabelSequence::hash() const
{
    size_t ret = 0;
    for (size_t i = 0; i < getLength(); ++i) {
        ret ^= std::hash<label_t>()(labels->at(i));
    }
    return ret;
};

shared_ptr<LabelSequence> LabelSequence::createEmptyLabelSequence() {
    return make_shared<LabelSequence>(make_shared<vector<label_t>>());
}

}  // namespace HighOrderCRF

