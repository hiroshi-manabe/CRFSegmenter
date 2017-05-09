#include <future>
#include <iostream>
#include <memory>
#include <queue>
#include <regex>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../DataConverter/SegmenterDataConverter.h"
#include "../DataConverter/TaggerDataConverter.h"
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../NgramDecoder/DictionaryDecoder.h"
#include "../Utility/StringUtil.h"
#include "KoreanAnalyzerClass.h"

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
using std::unordered_set;
using std::vector;

namespace KoreanAnalyzer {

enum optionIndex { UNKNOWN, HELP, THREADS, SEGMENTER_DICT, TAGGER_DICT, NGRAM_DICT, SEGMENTER_MODEL, TAGGER_MODEL, NGRAM_MODEL };

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
    { SEGMENTER_DICT, 0, "", "segmenter-dict", Arg::Required, "  --segmenter-dict  <file>\tDesignates the segmenter dictionary file (optional)." },
    { TAGGER_DICT, 0, "", "tagger-dict", Arg::Required, "  --tagger-dict  <file>\tDesignates the tagger dictionary file (optional)." },
    { NGRAM_DICT, 0, "", "ngram-dict", Arg::Required, "  --ngram-dict  <file>\tDesignates the ngrameme disambiguator dictionary file (optional)." },
    { SEGMENTER_MODEL, 0, "", "segmenter-model", Arg::Required, "  --segmenter-model  <file>\tDesignates the segmenter model file." },
    { TAGGER_MODEL, 0, "", "tagger-model", Arg::Required, "  --tagger-model  <file>\tDesignates the tagger model file." },
    { NGRAM_MODEL, 0, "", "ngram-model", Arg::Required, "  --ngram-model  <file>\tDesignates the ngrameme disambiguator model file." },
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

    if (!options[SEGMENTER_MODEL]) {
        cerr << "Segmenter model file not designated." << endl;
        exit(1);
    }
    if (!options[TAGGER_MODEL]) {
        cerr << "Tagger model file not designated." << endl;
        exit(1);
    }
    if (!options[NGRAM_MODEL]) {
        cerr << "Ngrameme disambiguator model file not designated." << endl;
        exit(1);
    }

    unordered_set<string> segmenterDicts;
    unordered_set<string> taggerDicts;
    unordered_set<string> ngramDicts;
    for (option::Option* opt = options[SEGMENTER_DICT]; opt; opt = opt->next()) {
        segmenterDicts.insert(opt->arg);
    }
    for (option::Option* opt = options[TAGGER_DICT]; opt; opt = opt->next()) {
        taggerDicts.insert(opt->arg);
    }
    for (option::Option* opt = options[NGRAM_DICT]; opt; opt = opt->next()) {
        ngramDicts.insert(opt->arg);
    }

    KoreanAnalyzerClass analyzer(segmenterDicts,
                        options[SEGMENTER_MODEL].arg,
                        taggerDicts,
                        options[TAGGER_MODEL].arg,
                        ngramDicts,
                        options[NGRAM_MODEL].arg);

    hwm::task_queue tq(numThreads);
    queue<future<vector<vector<string>>>> futureQueue;

    string line;
    const regex reNewLine(R"([\r\n]+$)");

    while (true) {
        getline(cin, line);
        if (cin) {
            string trimmed = regex_replace(line, reNewLine, "");
            future<vector<vector<string>>> f = tq.enqueue(&KoreanAnalyzerClass::analyze, &analyzer, line);
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

}  // namespace KoreanAnalyzer

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return KoreanAnalyzer::mainProc(argc, argv);
}
