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

using std::cerr;
using std::endl;
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
    int i = 1;
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
    vector<string> sequence;
    string line;
    
    while (getline(is, line) && !line.empty()) {
        sequence.emplace_back(move(line));
    }
    return generateFeaturesFromSequence(sequence);
}

vector<string> SegmenterDataConverter::generateFeaturesFromSequence(const vector<string> &sequence) const {
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

        bool hasSpace = (character.size() > 0 && character[0] == 0x20);
        size_t charCount = 0;
        auto ch = UnicodeCharacter::fromString(character.data() + hasSpace, character.size() - hasSpace, &charCount);
        if (charCount + hasSpace != character.size()) {
            cerr << "Only one character is allowed. " << endl << str << endl;
            exit(1);
        }

        auto possibleLabels = splitString(possibleLabelStr);
        unordered_set<string> possibleLabelSet(possibleLabels.begin(), possibleLabels.end());
        possibleLabelSetList.emplace_back(move(possibleLabelSet));

        labelList.emplace_back(move(label));

        observationList.emplace_back(ch, hasSpace);
    }
    
    ObservationSequence<CharWithSpace> obs(observationList, labelList, possibleLabelSetList, originalStringList);
    return obs.generateSequence(generator);
}

}  // namespace DataConverter
