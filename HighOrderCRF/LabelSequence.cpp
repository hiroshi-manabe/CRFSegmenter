#include <algorithm>
#include <memory>
#include <vector>

#include "LabelSequence.h"

namespace HighOrderCRF {

using std::make_shared;
using std::min;
using std::shared_ptr;
using std::vector;

LabelSequence::LabelSequence(vector<label_t> labels) {
    this->labels = labels;
}

size_t LabelSequence::getLength() const {
    return labels.size();
}

label_t LabelSequence::getLabelAt(size_t pos) const {
    if (pos >= labels.size()) {
        return INVALID_LABEL;
    }
    return labels.at(pos);
}

const label_t *LabelSequence::getLabelData() const {
    return labels.data();
}

label_t LabelSequence::getLastLabel() const {
    return getLabelAt(0);
}

LabelSequence LabelSequence::createPrefix() const {
    vector<label_t> seq(labels.begin() + 1, labels.end());
    return LabelSequence(seq);
}

size_t LabelSequence::getDifferencePosition(const LabelSequence &that) const {
    size_t minLength = min(getLength(), that.getLength());
    for (size_t i = 0; i < minLength; ++i) {
        if (getLabelAt(i) != that.getLabelAt(i)) {
            return i;
        }
    }
    return minLength;
}

bool LabelSequence::operator<(const LabelSequence &that) const {
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

bool LabelSequence::operator==(const LabelSequence &that) const {
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
        ret ^= std::hash<label_t>()(labels.at(i));
    }
    return ret;
};

LabelSequence LabelSequence::createEmptyLabelSequence() {
    return LabelSequence(vector<label_t>());
}

}  // namespace HighOrderCRF

