#include "DictionaryDecoder.h"

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../Utility/FileUtil.h"
#include "../Utility/StringUtil.h"

#include <iostream>
#include <future>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_set;
using std::vector;

namespace NgramDecoder {

enum optionIndex { UNKNOWN, HELP, THREADS, MODEL, DICT };

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
    { DICT, 0, "", "dict", Arg::Required, "  --dict  <file>\tDesignates the dictionary file to be loaded." },
    { MODEL, 0, "", "model", Arg::Required, "  --model  <number>\tDesignates the N-gram model file to be loaded." },
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

    unordered_set<string> dictionaries;
    for (option::Option* opt = options[DICT]; opt; opt = opt->next()) {
        dictionaries.insert(opt->arg);
    }

    string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(cerr, usage);
        return 1;
    }

    DictionaryDecoder decoder(modelFilename, dictionaries);

    hwm::task_queue tq(numThreads);
    queue<future<void>> futureQueue;

    while (true) {
        auto seq = Utility::readSequence(cin);
        vector<string> ret;
        vector<size_t> lengths;
        bool emptyFlag = seq.empty();
        future<void> f = tq.enqueue(&DictionaryDecoder::decode_and_return_lengths, decoder, seq, &ret, &lengths);
        futureQueue.push(move(f));

        if ((numThreads == 1 || !cin) && !futureQueue.empty()) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            futureQueue.front().get();
            futureQueue.pop();
            for (size_t i = 0; i < ret.size(); ++i) {
                cout << seq[i] << "\t" << ret[i] << "\n";
            }
            cout << endl;
        }
        if (!cin && emptyFlag && futureQueue.empty()) {
            break;
        }
    }

    return 0;
}

}  // namespace NgramDecoder

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return NgramDecoder::mainProc(argc, argv);
}
