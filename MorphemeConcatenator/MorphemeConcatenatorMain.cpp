#include "MorphemeConcatenatorClass.h"

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../Utility/FileUtil.h"
#include "../Utility/StringUtil.h"

#include <chrono>
#include <future>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MorphemeConcatenator {

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::future;
using std::move;
using std::queue;
using std::string;
using std::unordered_set;
using std::vector;

enum optionIndex { UNKNOWN, HELP, DICT, THREADS };

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
    { DICT, 0, "", "dict", Arg::Required, "  --dict  <file>\tDesignates the dictionary file to be loaded." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
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
        return 1;
    }

    if (options[HELP]) {
        option::printUsage(cout, usage);
        return 0;
    }

    size_t numThreads = 1;
    if (options[THREADS]) {
        char* endptr;
        int num = strtol(options[THREADS].arg, &endptr, 10);
        if (endptr == options[THREADS].arg || *endptr != 0 || num < 1) {
            cerr << "Illegal number of threads." << endl;
            exit(1);
        }
        numThreads = num;
    }

    unordered_set<string> dictionaries;
    for (option::Option* opt = options[DICT]; opt; opt = opt->next()) {
        dictionaries.insert(opt->arg);
    }

    MorphemeConcatenator::MorphemeConcatenatorClass s(dictionaries);
    
    string line;
    hwm::task_queue tq(numThreads);
    queue<future<vector<vector<string>>>> futureQueue;

    while (true) {
        auto seq = Utility::readSequence(cin);
        vector<vector<string>> seqSplit;
        seqSplit.reserve(seq.size());
        for (const auto &str : seq) {
            seqSplit.emplace_back(Utility::splitString(str));
        }
        bool emptyFlag = seqSplit.empty();
        auto f = tq.enqueue(&MorphemeConcatenator::MorphemeConcatenatorClass::concatenate, &s, seqSplit);
        futureQueue.push(move(f));

        if ((numThreads == 1 || !cin) && !futureQueue.empty()) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            const auto result = futureQueue.front().get();
            for (size_t i = 0; i < result.size(); ++i) {
                cout << Utility::join(result[i]) << endl;
            }
            futureQueue.pop();
            if (!(!cin && emptyFlag && futureQueue.empty())) {
                cout << endl;
            }
        }
        if (!cin && emptyFlag && futureQueue.empty()) {
            break;
        }
    }

    return 0;
}

}  // namespace MorphemeConcatenator

int main(int argc, char **argv) {
    return MorphemeConcatenator::mainProc(argc, argv);
}

