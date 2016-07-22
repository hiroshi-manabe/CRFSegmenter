#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SegmenterDataConverter.h"

#include "AggregatedFeatureTemplateGenerator.h"
#include "CharacterFeatureGenerator.h"
#include "CharacterTypeFeatureGenerator.h"
#include "CharWithSpace.h"
#include "CharWithSpaceFeatureGenerator.h"
#include "CharWithSpaceTypeFeatureGenerator.h"
#include "FeatureTemplateGenerator.h"
#include "ObservationSequence.h"
#include "SegmenterDictionaryFeatureGenerator.h"
#include "UnconditionalFeatureTemplateGenerator.h"

using std::istream;
using std::make_shared;
using std::move;
using std::stoi;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace DataConverter {

static vector<string> splitString(const string &s, char delim = '\t', int count = 0) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    int i = 0;
    while (getline(ss, item, (count && i >= count) ? '\0' : delim)) {
        elems.push_back(item);
        ++i;
    }
    return elems;
}

void SegmenterDataConverter::setOptions(const unordered_map<string, string> &argOptions) {
    unordered_map<string, string> defaultOptions {
        {"charMaxNgram", "3"},
        {"charMaxWindow", "3"},
        {"charMaxLabelLength", "4"},
        {"charTypeMaxNgram", "3"},
        {"charTypeMaxWindow", "3"},
        {"charTypeMaxLabelLength", "1"},
        {"dictMaxLabelLength", "5"},
    };
    options = argOptions;  // copy
    options.insert(defaultOptions.begin(), defaultOptions.end());

    auto gen = make_shared<AggregatedFeatureTemplateGenerator<CharWithSpace>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<CharWithSpace>>(1));
    gen->addFeatureTemplateGenerator(make_shared<CharacterFeatureGenerator>(stoi(options["charMaxNgram"]),
                                                                            stoi(options["charMaxWindow"]),
                                                                            stoi(options["charMaxLabelLength"])));
    
    gen->addFeatureTemplateGenerator(make_shared<CharacterTypeFeatureGenerator>(stoi(options["charTypeMaxNgram"]),
                                                                                stoi(options["charTypeMaxWindow"]),
                                                                                stoi(options["charTypeMaxLabelLength"])));
                                     
    if (options.find("containsSpaces") != options.end()) {
        gen->addFeatureTemplateGenerator(make_shared<CharWithSpaceFeatureGenerator>(stoi(options["charMaxNgram"]),
                                                                                    stoi(options["charMaxWindow"]),
                                                                                    stoi(options["charMaxLabelLength"])));
        gen->addFeatureTemplateGenerator(make_shared<CharWithSpaceTypeFeatureGenerator>(stoi(options["charTypeMaxNgram"]),
                                                                                        stoi(options["charTypeMaxWindow"]),
                                                                                        stoi(options["charTypeMaxLabelLength"])));
    }
    
    auto it = options.find("dictionaryFilename");
    if (it != options.end()) {
        gen->addFeatureTemplateGenerator(make_shared<SegmenterDictionaryFeatureGenerator>(it->second, stoi(options["dictMaxLabelLength"])));
    }
    optionSet = true;
    generator = gen;
}

vector<string> SegmenterDataConverter::generateFeaturesFromStream(istream& is) const {
    string line;
    getline(is, line);
    return generateFeaturesFromLine(line);
}

vector<string> SegmenterDataConverter::generateFeaturesFromLine(const string &line) const {
    assert(optionSet);
    
    // flags
    bool asciiSpaceOnly = options.find("asciiSpaceOnly") != options.end();
    bool concatenate = options.find("concatenate") != options.end();
    bool containsSpaces = options.find("containsSpaces") != options.end();
    bool isTraining = options.find("isTraining") != options.end();
    bool ignoreLatin = options.find("ignoreLatin") != options.end();
    
    const char *buf = line.c_str();
    size_t len = line.size();
    bool prevIsSpace = true;
    bool prevIsNBSP = false;
    vector<CharWithSpace> observationList;
    vector<string> labelList;

    size_t pos = 0;
    bool isAfterSlash = false;
    vector<unordered_set<string>> possibleLabelSetList;
    string prevCharType;

    while (pos < len) {
        size_t charCount = 0;
        auto uchar = UnicodeCharacter::fromString(buf + pos, len, &charCount);
        pos += charCount;
        bool isNBSP = uchar.getCodePoint() == 0xa0;
        bool isSpace = uchar.getCodePoint() == 0x20 || (!asciiSpaceOnly && (uchar.getCodePoint() == 0x3000 || isNBSP));

        if (isTraining && containsSpaces && isNBSP) {
            prevIsNBSP = true;
            continue;
        }
        if (isSpace) {
            prevIsSpace = true;
            continue;
        }
        
        if (observationList.empty()) {
            prevIsSpace = true;
        }
        
        bool insertSpace = false;
        bool cutFlag = false;
        bool noCutFlag = false;
        
        if (containsSpaces) {
            if (isTraining) {
                if ((concatenate && (prevIsNBSP || prevIsSpace)) || (!concatenate && prevIsSpace)) {
                    insertSpace = true;
                }
            }
            else {
                insertSpace = prevIsSpace;
            }
        }

        observationList.emplace_back(uchar, insertSpace);
        string charType = uchar.getCharacterType();

        if (containsSpaces) {
            if (!concatenate) {
                cutFlag = prevIsSpace;
            }
            else {
                noCutFlag = !(prevIsSpace || prevIsNBSP);
            }
        }

        bool isBetweenLatin = (prevCharType == "LATIN" && charType == "LATIN");
        if (isBetweenLatin && ignoreLatin) {
            if (prevIsSpace || prevIsNBSP) {
                cutFlag = true;
            }
            else {
                noCutFlag = true;
            }
        }
        
        bool correctLabel = false;
        if (isTraining) {
            if (containsSpaces && !concatenate) {
                correctLabel = prevIsNBSP || prevIsSpace;
            }
            else {
                correctLabel = prevIsSpace;
            }
        }
        if (cutFlag) {
            correctLabel = true;
        }
        if (noCutFlag) {
            correctLabel = false;
        }

        labelList.emplace_back(correctLabel ? "1" : "0");
        unordered_set<string> possibleLabelSet;

        if (cutFlag) {
            possibleLabelSet = decltype(possibleLabelSet){ "1" };
        }
        else if (noCutFlag) {
            possibleLabelSet = decltype(possibleLabelSet){ "0" };
        }
        else {
            possibleLabelSet = decltype(possibleLabelSet){ "0", "1" };
        }

        possibleLabelSetList.emplace_back(move(possibleLabelSet));
        prevIsSpace = false;
        prevIsNBSP = false;
        prevCharType = move(charType);
    }
    ObservationSequence<CharWithSpace> obs(observationList, labelList, possibleLabelSetList);
    return obs.generateSequence(generator);
}

}  // namespace DataConverter

