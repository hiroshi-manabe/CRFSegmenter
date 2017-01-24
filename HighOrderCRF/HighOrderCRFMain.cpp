#include <cstdlib>
#include <future>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "DataSequence.h"
#include "HighOrderCRFProcessor.h"
#include "types.h"

namespace HighOrderCRF {

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::make_shared;
using std::move;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;

enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, CALC_LIKELIHOOD, TEST, MODEL, THREADS, C1, C2, EPSILON, MAXITER };

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
    { MODEL, 0, "", "model", Arg::Required, "  --model  <file>\tDesignates the model file to be saved/loaded. Options will be saved to/loaded from <file>.options." },
    { TAG, 0, "", "tag", Arg::None, "  --tag  \tTag the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { CALC_LIKELIHOOD, 0, "", "calc-likelihood", Arg::None, "  --calc-likelihood  \tCalculates the likelihoods of labels at each position." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { C1, 0, "", "c1", Arg::Required, "  --c1  <number>\t(For training) Sets the coefficient for L1 regularization. The default value is 0.05 (defaults to 0 if the c2 is explicitly set)." },
    { C2, 0, "", "c2", Arg::Required, "  --c2  <number>\t(For training) Sets the coefficient for L2 regularization. The default value is 0 (no L2 regularization)." },
    { EPSILON, 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\t(For training) Sets the epsilon for convergence." },
    { MAXITER, 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\t(For training) Sets the maximum iteration count." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { 0, 0, 0, 0, 0, 0 }
};

// seq will be destroyed
vector<string> tag(const HighOrderCRFProcessor &processor, shared_ptr<DataSequence> seq) {
    vector<string> ret;
    vector<string> originalStringList = seq->getOriginalStringList();
    auto labelList = processor.tag(move(seq.get()));
    for (size_t i = 0; i < labelList.size(); ++i) {
        ret.emplace_back(originalStringList[i] + "\t" + labelList[i]);
    }
    return ret;
}

// seq will be destroyed
vector<string> calcLabelLikelihoods(const HighOrderCRFProcessor &processor, shared_ptr<DataSequence> seq) {
    vector<string> ret;
    vector<string> originalStringList = seq->getOriginalStringList();
    auto l = processor.calcLabelLikelihoods(seq.get());
    for (size_t i = 0; i < l.size(); ++i) {
        stringstream ss;
        ss << originalStringList[i];
        for (const auto &entry : l[i]) {
            ss << "\t" << entry.first << ":" << entry.second;
        }
        ret.emplace_back(ss.str());
        
    }
    return ret;
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

    string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(cerr, usage);
        return 1;
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
    
    if (options[TRAIN]) {
        string filename = options[TRAIN].arg;
        double c1 = 0.0;
        double c2 = 0.0;
        double epsilon = 0.0;
        int maxIter = 0;

        if (options[EPSILON]) {
            epsilon = atof(options[EPSILON].arg);
        }
        if (options[MAXITER]) {
            maxIter = atoi(options[MAXITER].arg);
        }
        if (options[C1]) {
            c1 = atof(options[C1].arg);
        }
        if (options[C2]) {
            c2 = atof(options[C2].arg);
        }
        if (c1 == 0.0 && c2 == 0.0) {
            c1 = 0.05;
        }
        
        HighOrderCRFProcessor processor;
        processor.train(filename, numThreads, maxIter, c1, c2, epsilon);
        processor.writeModel(modelFilename);
        
        return 0;
    }
    else if (options[TEST]) {
        string filename = options[TEST].arg;
        HighOrderCRFProcessor proc;
        proc.readModel(modelFilename);
        proc.test(filename, numThreads);

        return 0;
    }
    // --tag or --calc-likelihood
    else {
        HighOrderCRFProcessor proc;
        proc.readModel(modelFilename);

        hwm::task_queue tq(numThreads);
        queue<future<vector<string>>> futureQueue;

        while (true) {
            auto seq = make_shared<DataSequence>(cin);
            bool emptyFlag = seq->empty();
            if (!emptyFlag) {
                future<vector<string>> f = (options[CALC_LIKELIHOOD] ?
                                        tq.enqueue(&calcLabelLikelihoods, proc, seq) :
                                        tq.enqueue(&tag, proc, seq));
                futureQueue.push(move(f));
            }
            if ((numThreads == 1 || !cin) && !futureQueue.empty()) {
                futureQueue.front().wait();
            }
            while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                auto ret = futureQueue.front().get();
                for (const auto &str : ret) {
                    cout << str << "\n";
                }
                cout << endl;
                futureQueue.pop();
            }
            if (!cin && emptyFlag && futureQueue.empty()) {
                break;
            }
        }
    }
    return 0;
}

} // namespace HighOrderCRF

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return HighOrderCRF::mainProc(argc, argv);
}
