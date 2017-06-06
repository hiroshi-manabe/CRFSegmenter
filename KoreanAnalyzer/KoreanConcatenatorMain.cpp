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
#include "../HighOrderCRF/DataSequence.h"
#include "../HighOrderCRF/FeatureTemplate.h"
#include "../HighOrderCRF/HighOrderCRFProcessor.h"
#include "../Utility/StringUtil.h"
#include "KoreanConcatenatorClass.h"

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

enum optionIndex {
    UNKNOWN, HELP, THREADS,
    CONCATENATOR_DICT, CONCATENATOR_MODEL, CONCATENATOR_ORDER,
};

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
    { CONCATENATOR_DICT, 0, "", "concatenator-dict", Arg::Required, "  --concatenator-dict  <file>\tDesignates the concatenator dictionary file (optional)." },
    { CONCATENATOR_MODEL, 0, "", "concatenator-model", Arg::Required, "  --concatenator-model  <file>\tDesignates the concatenator model file." },
    { CONCATENATOR_ORDER, 0, "", "concatenator-order", Arg::Required, "  --concatenator-order  \tDesignates the concatenator CRF order (optional). Defaults to 3." },
    { 0, 0, 0, 0, 0, 0 }
};

int concatenatorMain(int argc, char **argv) {
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

    size_t concatenatorOrder = 3;
    if (options[CONCATENATOR_ORDER]) {
        int num = atoi(options[CONCATENATOR_ORDER].arg);
        if (num < 0) {
            cerr << "Illegal order" << endl;
            exit(1);
        }
        concatenatorOrder = num;
    }

    if (!options[CONCATENATOR_MODEL]) {
        cerr << "Concatenator model file not designated." << endl;
        exit(1);
    }

    unordered_set<string> concatenatorDicts;
    for (option::Option* opt = options[CONCATENATOR_DICT]; opt; opt = opt->next()) {
        concatenatorDicts.insert(opt->arg);
    }

    KoreanConcatenatorClass concatenator(concatenatorDicts,
                                         options[CONCATENATOR_MODEL].arg,
                                         concatenatorOrder);

    hwm::task_queue tq(numThreads);
    queue<future<string>> futureQueue;

    string line;
    const regex reNewLine(R"([\r\n]+$)");

    while (true) {
        getline(cin, line);
        if (cin) {
            string trimmed = regex_replace(line, reNewLine, "");
            future<string> f = tq.enqueue(&KoreanConcatenatorClass::concatenate, &concatenator, line);
            futureQueue.push(move(f));
        }
        if (numThreads == 1 && !futureQueue.empty()) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto result = futureQueue.front().get();
            cout << result << endl;
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
    return KoreanAnalyzer::concatenatorMain(argc, argv);
}
