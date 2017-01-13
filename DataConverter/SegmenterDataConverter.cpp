#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SegmenterDataConverter.h"

#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
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

using std::cerr;
using std::endl;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace DataConverter {

extern vector<string> splitString(const string &s, char delim = '\t', int count = 0);

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

shared_ptr<HighOrderCRF::DataSequence> SegmenterDataConverter::toDataSequence(const vector<string> &sequence) const {
    assert(optionSet);

    vector<string> originalStringList;
    vector<CharWithSpace> observationList;
    vector<string> labelList;
    vector<unordered_set<string>> possibleLabelSetList;

    originalStringList.reserve(sequence.size());
    observationList.reserve(sequence.size());
    labelList.reserve(sequence.size());
    possibleLabelSetList.reserve(sequence.size());

    for (const auto &str : sequence) {
        auto fields = splitString(str, '\t');
        if (fields.size() != 3) {
            cerr << "A line must contain 3 fields: Character[TAB]Possible labels[TAB]label." << endl << str << endl;
            exit(1);
        }
        string &character = fields[0];
        string &possibleLabelStr = fields[1];
        string &label = fields[2];
        originalStringList.emplace_back(character);

        bool hasSpace = (character.size() > 1 && character[0] == 0x20);
        size_t charCount = 0;
        auto ch = UnicodeCharacter::fromString(character.begin() + hasSpace, character.size() - hasSpace, &charCount);
        if (charCount + hasSpace != character.size()) {
            cerr << "Only one character is allowed. " << endl << str << endl;
            exit(1);
        }
        auto possibleLabels = splitString(possibleLabelStr, ',');
        unordered_set<string> possibleLabelSet(possibleLabels.begin(), possibleLabels.end());
        possibleLabelSetList.emplace_back(move(possibleLabelSet));
        labelList.emplace_back(move(label));
        observationList.emplace_back(ch, hasSpace);
    }
    return make_shared<HighOrderCRF::DataSequence>(move(originalStringList), move(labelList), move(possibleLabelSetList), generator->generateFeatureTemplates(observationList));
}

}  // namespace DataConverter
