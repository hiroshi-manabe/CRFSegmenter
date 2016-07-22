#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "TaggerDataConverter.h"

#include "../Dictionary/DictionaryClass.h"
#include "AggregatedFeatureTemplateGenerator.h"
#include "DictionaryFeatureGenerator.h"
#include "FeatureTemplateGenerator.h"
#include "ObservationSequence.h"
#include "UnconditionalFeatureTemplateGenerator.h"
#include "WordFeatureGenerator.h"

using std::istream;
using std::make_shared;
using std::move;
using std::stoi;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using Dictionary::DictionaryClass;

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

void TaggerDataConverter::setOptions(const unordered_map<string, string> &argOptions) {
    unordered_map<string, string> defaultOptions {
        {"wordMaxNgram", "2"},
        {"wordMaxWindow", "2"},
        {"wordMaxLabelLength", "4"},
    };
    options = argOptions;  // copy
    options.insert(defaultOptions.begin(), defaultOptions.end());

    auto gen = make_shared<AggregatedFeatureTemplateGenerator<string>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<string>>(2));
    gen->addFeatureTemplateGenerator(make_shared<WordFeatureGenerator>(stoi(options["wordMaxNgram"]),
                                                                       stoi(options["wordMaxWindow"]),
                                                                       stoi(options["wordMaxLabelLength"])));
    
    auto it = options.find("dictionaryFilename");
    if (it != options.end()) {
        dictionary = make_shared<DictionaryClass>(it->second);
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(dictionary));
    }
    optionSet = true;
    generator = gen;
}

vector<string> TaggerDataConverter::generateFeaturesFromStream(istream& is) const {
    vector<string> sequence;
    string line;
    
    while (getline(is, line) && !line.empty()) {
        sequence.emplace_back(move(line));
    }
    return generateFeaturesFromSequence(sequence);
}

vector<string> TaggerDataConverter::generateFeaturesFromSequence(const vector<string> &sequence) const {
    assert(optionSet);
    vector<string> observationList;
    vector<string> labelList;
    vector<unordered_set<string>> possibleLabelSetList;
    observationList.reserve(sequence.size());
    labelList.reserve(sequence.size());
    possibleLabelSetList.reserve(sequence.size());

    for (const auto &str : sequence) {
        auto wordAndLabel = splitString(str, '\t');
        if (wordAndLabel.size() < 2) {
            wordAndLabel.emplace_back("*");
        }
        string &word = wordAndLabel[0];
        string &label = wordAndLabel[1];
        
        unordered_set<string> possibleLabelSet;
        if (dictionary) {
            vector<vector<const string *>> labelListList = dictionary->lookup(word);
            if (!labelListList.empty()) {
                for (const auto &labelList : labelListList) {
                    assert(labelList.size() == 1);
                    possibleLabelSet.insert(*labelList[0]);
                }
                if (label != "*") {
                    possibleLabelSet.insert(label);
                }
            }
        }
        possibleLabelSetList.emplace_back(move(possibleLabelSet));
        labelList.emplace_back(move(label));
        observationList.emplace_back(move(word));
    }
    
    ObservationSequence<string> obs(observationList, labelList, possibleLabelSetList);
    return obs.generateSequence(generator);
}

}  // namespace DataConverter

