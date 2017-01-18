#include <cassert>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#include "TaggerDataConverter.h"

#include "../Dictionary/DictionaryClass.h"
#include "../Utility/SplitString.h"
#include "AggregatedFeatureTemplateGenerator.h"
#include "DictionaryFeatureGenerator.h"
#include "FeatureTemplateGenerator.h"
#include "ObservationSequence.h"
#include "UnconditionalFeatureTemplateGenerator.h"
#include "WordCharacterFeatureGenerator.h"
#include "WordCharacterTypeFeatureGenerator.h"
#include "WordFeatureGenerator.h"

using std::make_shared;
using std::move;
using std::set;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::unordered_map;
using std::vector;

namespace DataConverter {

TaggerDataConverter::TaggerDataConverter(const unordered_map<string, string> &argOptions) {
    unordered_map<string, string> defaultOptions {
        {"characterLength", "2"},
        {"characterTypeLength", "2"},
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
    size_t characterLength = stoi(options["characterLength"]);
    if (characterLength > 0) {
        gen->addFeatureTemplateGenerator(make_shared<WordCharacterFeatureGenerator>(characterLength));
    }
    size_t characterTypeLength = stoi(options["characterTypeLength"]);
    if (characterTypeLength > 0) {
        gen->addFeatureTemplateGenerator(make_shared<WordCharacterTypeFeatureGenerator>(characterTypeLength));
    }
    
    auto it = options.find("dictionaryFilename");
    if (it != options.end()) {
        dictionary = make_shared<Dictionary::DictionaryClass>(it->second);
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(dictionary));
    }
    optionSet = true;
    generator = gen;
}

shared_ptr<HighOrderCRF::DataSequence> TaggerDataConverter::toDataSequence(const vector<string> &sequence) const {
    assert(optionSet);
    vector<string> originalStringList;
    vector<string> observationList;
    vector<string> labelList;
    vector<set<string>> possibleLabelSetList;

    originalStringList.reserve(sequence.size());
    observationList.reserve(sequence.size());
    labelList.reserve(sequence.size());
    possibleLabelSetList.reserve(sequence.size());

    for (const auto &str : sequence) {
        auto wordAndLabel = Utility::splitString(str);
        if (wordAndLabel.size() < 2) {
            wordAndLabel.emplace_back("*");
        }
        string &word = wordAndLabel[0];
        string &label = wordAndLabel[1];
        
        set<string> possibleLabelSet;
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
        originalStringList.emplace_back(word);
        possibleLabelSetList.emplace_back(move(possibleLabelSet));
        labelList.emplace_back(move(label));
        observationList.emplace_back(move(word));
    }
    
    return make_shared<HighOrderCRF::DataSequence>(move(originalStringList), move(labelList), move(possibleLabelSetList), generator->generateFeatureTemplates(observationList));
}

}  // namespace DataConverter

