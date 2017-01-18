#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <queue>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../DataConverter/UnicodeCharacter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorClass.h"

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::for_each;
using std::future;
using std::getline;
using std::queue;
using std::regex;
using std::shared_ptr;
using std::sregex_token_iterator;
using std::string;
using std::transform;
using std::unordered_map;
using std::vector;

using DataConverter::UnicodeCharacter;

namespace JapaneseAnalyzer {

enum optionIndex { UNKNOWN, HELP, THREADS, SEGMENTER_DICT, TAGGER_DICT, MORPH_DICT, SEGMENTER_MODEL, TAGGER_MODEL, MORPH_MODEL };

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
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { SEGMENTER_DICT, 0, "", "segmenter-dict", Arg::Required, "  --segmenter-dict  <file>\tDesignates the segmenter dictionary file." },
    { TAGGER_DICT, 0, "", "tagger-dict", Arg::Required, "  --tagger-dict  <file>\tDesignates the tagger dictionary file." },
    { MORPH_DICT, 0, "", "morph-dict", Arg::Required, "  --morph-dict  <file>\tDesignates the morpheme disambiguator dictionary file." },
    { SEGMENTER_MODEL, 0, "", "segmenter-model", Arg::Required, "  --segmenter-model  <file>\tDesignates the segmenter model file." },
    { TAGGER_MODEL, 0, "", "tagger-model", Arg::Required, "  --tagger-model  <file>\tDesignates the tagger model file." },
    { MORPH_MODEL, 0, "", "morph-model", Arg::Required, "  --morph-model  <file>\tDesignates the morpheme disambiguator model file." },
    { 0, 0, 0, 0, 0, 0 }
};

vector<UnicodeCharacter> toUnicodeCharacterList(const string &orig) {
    vector<UnicodeCharacter> ret;
    for (auto it = orig.begin(); it != orig.end(); ) {
        size_t charCount;
        ret.emplace_back(UnicodeCharacter::fromString(it, orig.end() - it, &charCount));
        it += charCount;
    }
    return ret;
}

string toString(const vector<UnicodeCharacter> &origChars) {
    string ret;
    for (const auto c : origChars) {
        ret += c.toString();
    }
    return ret;
}

vector<UnicodeCharacter> toHankaku(const vector<UnicodeCharacter> &origChars) {
    vector<UnicodeCharacter> ret(origChars.size());
    transform(origChars.begin(),
              origChars.end(),
              ret.begin(),
              [](UnicodeCharacter ch) {
                  auto c = ch.getCodePoint();
                  return ((c >= 0xff01 &&
                           c <= 0xff5e) ?
                          UnicodeCharacter(c - 0xfee0) : ch);
              });
    return ret;
}

string replaceWithNonChar(const string &input, const regex &re) {
    string ret;
    bool isMatch = false;
    static uint32_t nonCharCode = 0;
    
    auto callback = [&](const string &m) {
        if (isMatch) {
            string nonChar = UnicodeCharacter(0xfdd0 + nonCharCode).toString();
            for (size_t i = 0; i < m.size(); ++i) {
                ret += nonChar;
            }
            nonCharCode = (nonCharCode + 1) % 0x20;
        }
        else {
            ret += m;
        }
        isMatch = !isMatch;
    };
    
    sregex_token_iterator begin(input.begin(), input.end(), re, {-1, 0});
    sregex_token_iterator end;
    for_each(begin, end, callback);
    
    return ret;
}

bool isNonCharCode(uint32_t code) {
    return code >= 0xfdd0 && code <= 0xfdef;
}

vector<string> toSegmenterInput(const string &input) {
    static const regex regexUrl(R"([a-z]+://[\-_.!~*'()a-zA-Z0-9;/?:@&=+$,%#]+)");
    static const regex regexEmail(R"((?:mailto:)?[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~\-]+@[a-zA-Z0-9\-]+(?:.[a-zA-Z0-9\-]+)*)");
    static const regex regexNumber(R"([\d\.,]*[\d\.])");

    auto origChars = toUnicodeCharacterList(input);
    string processed = toString(toHankaku(origChars));
    processed = replaceWithNonChar(processed, regexUrl);
    processed = replaceWithNonChar(processed, regexEmail);
    processed = replaceWithNonChar(processed, regexNumber);
    auto processedChars = toUnicodeCharacterList(processed);
    assert(origChars.size() == processedChars.size());

    vector<string> ret;
    uint32_t prevProcessedCharCode;
    
    for (size_t i = 0; i < origChars.size(); ++i) {
        bool hasSpace;
        string possibleLabelStr("0,1");
        
        auto ch = origChars[i];
        auto sp = UnicodeCharacter(0);
        if (i < origChars.size() - 1 &&
            (ch.getCodePoint() == 0x20 || ch.getCodePoint == 0xa0)){
            sp = ch;
            ++i;
            ch = origChars[i];
        }
        
        auto processedCharCode = processedChars[i].getCodePoint();
        hasSpace = (i == 0 || sp.getCodePoint() == 0x20);
        
        if (hasSpace) {
            possibleLabelStr = "1";
        }
        else if (isNonCharCode(prevProcessedCharCode) &&
                 isNonCharCode(processedCharCode)) {
            if (prevProcessedCharCode == processedCharCode) {
                possibleLabelStr = "0";
            }
            else {
                possibleLabelStr = "1";
            }
        }
        ret.emplace_back(string(hasSpace ? " " : "") +
                         ch.toString() +
                         "\t" +
                         possibleLabelStr +
                         "\t" +
                         "*");
    }
    return ret;
}

vector<string> analyze(const DataConverter::DataConverterInterface &segmenterConverter,
                       const HighOrderCRF::HighOrderCRFProcessor &segmenterProcessor,
                       const DataConverter::DataConverterInterface &taggerConverter,
                       const HighOrderCRF::HighOrderCRFProcessor &taggerProcessor,
                       const MorphemeDisambiguator::MorphemeDisambiguatorClass &morphemeDisambiguator,
                       const string line) {
    auto segmenterInput = toSegmenterInput(line);
    auto dataSequence = segmenterConverter.toDataSequence(segmenterInput);
    auto segmenterOutput = segmenterProcessor.tag(dataSequence.get());
}

int mainProc(int argc, char **argv) {
    argv += (argc > 0);
    argc -= (argc > 0);
    
    option::Stats stats(usage, argc, argv);
    vector<option::Option> options(stats.options_max);
    vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error()) {
        option::printUsage(cerr, usage);
        return 1;
    }

    for (auto &option : options) {
        if (option.desc && option.desc->index == UNKNOWN) {
            cerr << "Unknown option: " << option.name << endl;
            option::printUsage(cout, usage);
            return 1;
        }
    }

    if (options[HELP]) {
        option::printUsage(cout, usage);
        return 0;
    }

    size_t numThreads = 1;
    if (options[THREADS]) {
        int num = atoi(options[THREADS].arg);
        if (num < 1) {
            cerr << "Illegal number of threads" << endl;
            exit(1);
        }
        numThreads = num;
    }
    
    unordered_map<string, string> segmenterOptions;
    unordered_map<string, string> taggerOptions;
    unordered_map<string, string> morphOptions;

    if (!options[SEGMENTER_DICT]) {
        cerr << "Segmenter dictionary file not designated." << endl;
        exit(1);
    }
    if (!options[TAGGER_DICT]) {
        cerr << "Tagger dictionary file not designated." << endl;
        exit(1);
    }
    if (!options[MORPH_DICT]) {
        cerr << "Morpheme disambiguator dictionary file not designated." << endl;
        exit(1);
    }
    if (!options[SEGMENTER_MODEL]) {
        cerr << "Segmenter model file not designated." << endl;
        exit(1);
    }
    if (!options[TAGGER_MODEL]) {
        cerr << "Tagger model file not designated." << endl;
        exit(1);
    }
    if (!options[MORPH_MODEL]) {
        cerr << "Morpheme disambiguator model file not designated." << endl;
        exit(1);
    }

    segmenterOptions["dictionaryFileName"] = options[SEGMENTER_DICT].arg;
    taggerOptions["dictionaryFileName"] = options[TAGGER_DICT].arg;
    morphOptions["dictionaryFileName"] = options[MORPH_DICT].arg;

    hwm::task_queue tq(numThreads);
    queue<future<vector<string>>> futureQueue;

    DataConverter::SegmenterDataConverter segmenterConverter(segmenterOptions);
    HighOrderCRF::HighOrderCRFProcessor segmenterProcessor;
    segmenterProcessor.readModel(options[SEGMENTER_MODEL].arg);
    DataConverter::TaggerDataConverter taggerConverter(taggerOptions);
    HighOrderCRF::HighOrderCRFProcessor taggerProcessor;
    taggerProcessor.readModel(options[TAGGER_MODEL].arg);
    MorphemeDisambiguator::MorphemeDisambiguatorClass morph(morphOptions);
    morph.readModel(options[MORPH_MODEL].arg);

    string line;
    regex reNewLine(R"(\r?\n$)")); 
    while (getline(cin, line)) {
        string trimmed = regex_replace(line, reNewLine, "");
        future<vector<string>> f = tq.enqueue(analyze, segmenterConverter, segmenterProcessor, taggerConverter, taggerProcessor, morph, line);
    }
}  // namespace JapaneseAnalyzer

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return JapaneseAnalyzer::mainProc(argc, argv);
}
