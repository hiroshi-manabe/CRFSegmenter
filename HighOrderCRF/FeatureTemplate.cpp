#include "FeatureTemplate.h"

#include "../Utility/StringUtil.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using std::cerr;
using std::endl;
using std::exit;
using std::stoi;
using std::string;
using std::to_string;

namespace HighOrderCRF {

FeatureTemplate::FeatureTemplate(const string tag, size_t labelLength) {
    this->tag = tag;
    this->labelLength = labelLength;
}

FeatureTemplate::FeatureTemplate(const string str) {
    auto labelLengthAndTag = Utility::splitString(str, ':', 2);
    if (labelLengthAndTag.size() == 2) {
        this->labelLength = stoi(labelLengthAndTag[0]);
        this->tag = labelLengthAndTag[1];
    }
    else {
        cerr << "Invalid feature template: " << str << endl;
        exit(1);
    }
}

size_t FeatureTemplate::getLabelLength() const {
    return labelLength;
}
        
const string &FeatureTemplate::getTag() const {
    return tag;
}

string FeatureTemplate::toString() const {
    auto ret = to_string(this->labelLength);
    ret += ":";
    ret += this->tag;
    return ret;
}
    
bool FeatureTemplate::operator==(const FeatureTemplate &that) const {
    return this->getLabelLength() == that.getLabelLength() && this->tag == that.tag;
}
    
size_t FeatureTemplate::hash() const {
    return std::hash<string>()(tag) ^ std::hash<size_t>()(labelLength);
}

}  // namespace HighOrderCRF
