#include <future>
#include <iostream>
#include <memory>
#include <queue>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorOptions.h"
#include "../MorphemeDisambiguator/MorphemeDisambiguatorClass.h"
#include "../Utility/StringUtil.h"
#include "JapaneseAnalyzer.h"

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::getline;
using std::move;
using std::queue;
using std::regex;
using std::string;
using std::unordered_map;
using std::vector;

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

    JapaneseAnalyzer analyzer(options[SEGMENTER_DICT].arg,
                              options[SEGMENTER_MODEL].arg,
                              options[TAGGER_DICT].arg,
                              options[TAGGER_MODEL].arg,
                              options[MORPH_DICT].arg,
                              options[MORPH_MODEL].arg);

    hwm::task_queue tq(numThreads);
    queue<future<vector<vector<string>>>> futureQueue;

    string line;
    const regex reNewLine(R"([\r\n]+$)");

    while (true) {
        getline(cin, line);
        if (cin) {
            string trimmed = regex_replace(line, reNewLine, "");
            future<vector<vector<string>>> f = tq.enqueue(&JapaneseAnalyzer::analyze, &analyzer, line);
            futureQueue.push(move(f));
        }
        if (numThreads == 1 && !futureQueue.empty()) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto result = futureQueue.front().get();
            for (const auto &s : result) {
                cout << Utility::join(s) << "\n";
            }
            cout << endl;
            futureQueue.pop();
        }
        if (!cin && futureQueue.empty()) {
            break;
        }
    }
    return 0;
}

}  // namespace JapaneseAnalyzer

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return JapaneseAnalyzer::mainProc(argc, argv);
}
