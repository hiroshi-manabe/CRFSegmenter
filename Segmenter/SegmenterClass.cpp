#include "SegmenterClass.h"

#include "../HighOrderCRF/AggregatedFeatureTemplateGenerator.h"
#include "../HighOrderCRF/FeatureTemplateGenerator.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../HighOrderCRF/ObservationSequence.h"
#include "../HighOrderCRF/UnconditionalFeatureTemplateGenerator.h"
#include "CharacterFeatureGenerator.h"
#include "CharacterTypeFeatureGenerator.h"
#include "DictionaryFeatureGenerator.h"
#include "optionparser.h"
#include "TrainingOptions.h"
#include "UnicodeCharacter.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Segmenter {

using HighOrderCRF::AggregatedFeatureTemplateGenerator;
using HighOrderCRF::FeatureTemplateGenerator;
using HighOrderCRF::HighOrderCRFProcessor;
using HighOrderCRF::ObservationSequence;
using HighOrderCRF::UnconditionalFeatureTemplateGenerator;

using std::endl;
using std::cout;
using std::cerr;
using std::getline;
using std::ifstream;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;

shared_ptr<ObservationSequence<UnicodeCharacter>> convertLineToObservationSequence(const string &line, bool hasValidLabels) {
    const char *buf = line.c_str();
    size_t len = line.size();
    bool prevIsSpace = true;
    auto observationList = make_shared<vector<UnicodeCharacter>>();
    auto labelList = make_shared<vector<string>>();

#ifdef EMULATE_BOS_EOS
    observationList->push_back(UnicodeCharacter(0));
    labelList->push_back("__BOS_EOS__");
#endif

    size_t pos = 0;
    bool isAfterSlash = false;
    while (pos < len) {
        size_t charCount = 0;
        auto uchar = UnicodeCharacter::fromString(buf + pos, len, &charCount);
        pos += charCount;
        if (uchar.getCodePoint() == ' ') {
            prevIsSpace = true;
            isAfterSlash = false;
            continue;
        }
        else if (uchar.getCodePoint() == '/') {
            isAfterSlash = true;
            continue;
        }
        else {
            if (isAfterSlash) {
                continue;
            }
            observationList->push_back(uchar);
            labelList->push_back(prevIsSpace ? "1" : "0");
            prevIsSpace = false;
        }
    }
#ifdef EMULATE_BOS_EOS
    observationList->push_back(UnicodeCharacter(0));
    labelList->push_back("__BOS_EOS__");
#endif
    return make_shared<ObservationSequence<UnicodeCharacter>>(observationList, labelList, hasValidLabels);
}

SegmenterClass::SegmenterClass(const TrainingOptions &options) {
    auto gen = make_shared<AggregatedFeatureTemplateGenerator<UnicodeCharacter>>();
    gen->addFeatureTemplateGenerator(make_shared<UnconditionalFeatureTemplateGenerator<UnicodeCharacter>>(1));
    gen->addFeatureTemplateGenerator(make_shared<CharacterFeatureGenerator>(options.charMaxNgram,
                                                                            options.charMaxWindow,
                                                                            options.charMaxLabelLength));
    gen->addFeatureTemplateGenerator(make_shared<CharacterTypeFeatureGenerator>(options.charTypeMaxNgram,
                                                                                options.charTypeMaxWindow,
                                                                                options.charTypeMaxLabelLength));
    if (!options.dictionaryFilename.empty()) {
        gen->addFeatureTemplateGenerator(make_shared<DictionaryFeatureGenerator>(options.dictionaryFilename));
    }
    featureGenerator = gen;
};

shared_ptr<vector<shared_ptr<ObservationSequence<UnicodeCharacter>>>> SegmenterClass::readData(const string &fileName, bool hasValidLabels) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cerr << "Cannot read from file: " << fileName << endl;
        exit(1);
    }
    auto observationSequenceList = make_shared<vector<shared_ptr<ObservationSequence<UnicodeCharacter>>>>();
    string line;
    while (getline(ifs, line)) {
        observationSequenceList->push_back(convertLineToObservationSequence(line, hasValidLabels));
    }
    ifs.close();
    return observationSequenceList;
}

void SegmenterClass::train(const string &trainingFilename,
    const string &modelFilename) {
    auto observationSequenceList = readData(trainingFilename, true);
    CRFProcessor = make_shared<HighOrderCRFProcessor<UnicodeCharacter>>();
    CRFProcessor->train(observationSequenceList, featureGenerator, 10000, false, 10.0, 0.00001);
    CRFProcessor->writeModel(modelFilename);
}

string SegmenterClass::segment(const string &line) const {
    auto observationSequence = convertLineToObservationSequence(line, false);
    auto spaceList = CRFProcessor->tag(observationSequence, featureGenerator);
    auto unicodeList = observationSequence->getObservationList();
    string ret;
    for (size_t i = 0; i < unicodeList->size(); ++i) {
        if (i > 0 && (*spaceList)[i] == "1") {
            ret += " ";
        }
        ret += (*unicodeList)[i].toString();
    }
    return ret;
}

void SegmenterClass::test(const string &testFilename) {
    auto observationSequenceList = readData(testFilename, true);
    auto labelListList = make_shared<vector<shared_ptr<vector<string>>>>();
    for (auto &observationSequence : *observationSequenceList) {
        labelListList->push_back(observationSequence->getLabelList());
    }
    CRFProcessor->test(observationSequenceList, featureGenerator, labelListList);
}

void SegmenterClass::readModel(const string &modelFilename) {
    CRFProcessor = make_shared<HighOrderCRFProcessor<UnicodeCharacter>>();
    CRFProcessor->readModel(modelFilename);
}

}  // namespace Segmenter

enum optionIndex { UNKNOWN, HELP, TRAIN, SEGMENT, TEST, MODEL, DICT };

struct Arg : public option::Arg
{

    static option::ArgStatus Required(const option::Option& option, bool msg)
    {
        if (option.arg != 0) {
            return option::ARG_OK;
        }

        return option::ARG_ILLEGAL;
    }
};

const option::Descriptor usage[] =
{
    { UNKNOWN, 0, "", "", Arg::None, "USAGE:  [options]\n\n"
    "Options:" },
    { HELP, 0, "h", "help", Arg::None, "  -h, --help  \tPrints usage and exit." },
    { MODEL, 0, "", "model", Arg::Required, "  --model  <file>\tDesignates the model file to be saved/loaded." },
    { DICT, 0, "", "dict", Arg::Required, "  --dict  <file>\tDesignates the dictionary file to be loaded." },
    { SEGMENT, 0, "", "segment", Arg::None, "  --segment  \tSegments text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { UNKNOWN, 0, "", "", Arg::None, "Examples:\n"
    "  Segmenter --train train.txt --model model.dat\n"
    "  Segmenter --test test.txt --model model.dat\n"
    "  Segmenter --segment < input_file > output_file"
    },
    { 0, 0, 0, 0, 0, 0 }
};


int main(int argc, char **argv) {
    Segmenter::TrainingOptions op = { 3, 3, 4, 3, 3, 1, "" };

    argv += (argc > 0);
    argc -= (argc > 0);

    option::Stats stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error()) {
        return 1;
    }

    if (options[HELP]) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    std::string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(std::cerr, usage);
        return 0;
    }

    std::string dictFilename;
    if (options[DICT]) {
        dictFilename = options[DICT].arg;
        op.dictionaryFilename = dictFilename;
    }

    if (options[TRAIN]) {
        std::string trainingFilename = options[TRAIN].arg;
        Segmenter::SegmenterClass s(op);
        s.train(trainingFilename, modelFilename);
        return 0;
    }

    if (options[TEST]) {
        std::string testFilename = options[TEST].arg;
        Segmenter::SegmenterClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // SEGMENT or none
    Segmenter::SegmenterClass s(op);
    s.readModel(modelFilename);
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << s.segment(line) << std::endl;
    }

    return 0;
}

