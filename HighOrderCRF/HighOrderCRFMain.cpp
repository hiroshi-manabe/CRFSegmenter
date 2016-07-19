#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "HighOrderCRFProcessor.h"
#include "types.h"

#include <cstdlib>
#include <future>
#include <iostream>
#include <queue>

namespace HighOrderCRF {

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::getline;
using std::queue;

enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, CALC_LIKELIHOOD, TEST, MODEL, THREADS, REGTYPE, COEFF, EPSILON, MAXITER };

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
    { UNKNOWN, "UNKNOWN", 0, "", "", Arg::None, "USAGE:  [options]\n\n"
    "Options:" },
    { HELP, "HELP", 0, "h", "help", Arg::None, "  -h, --help  \tPrints usage and exit." },
    { MODEL, "MODEL", 0, "", "model", Arg::Required, "  --model  <file>\tDesignates the model file to be saved/loaded. Options will be saved to/loaded from <file>.options." },
    { TAG, "TAG", 0, "", "tag", Arg::None, "  --tag  \tTag the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { CALC_LIKELIHOOD, "CALC_LIKELIHOOD", 0, "", "calc-likelihood", Arg::None, "  --calc-likelihood  \tCalculates the likelihoods of labels at each position." },
    { TEST, "TEST", 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, "TRAIN", 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { REGTYPE, "REGTYPE", 0, "", "regtype", Arg::Required, "  --regtype  <type>\t(For training) Designates the regularization type (\"L1\" / \"L2\") for optimization." },
    { COEFF, "COEFF", 0, "", "coeff", Arg::Required, "  --coeff  <number>\t(For training) Sets the regularization coefficient." },
    { EPSILON, "EPSILON", 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\t(For training) Sets the epsilon for convergence." },
    { MAXITER, "MAXITER", 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\t(For training) Sets the maximum iteration count." },
    { THREADS, "THREADS", 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
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

    string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(cerr, usage);
        return 1;
    }

    int numThreads = 1;
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
        double coeff;
        double epsilon;
        int maxIter;
        string regType;

        if (options[COEFF]) {
            coeff = atof(options[COEFF].arg);
        }
        if (options[EPSILON]) {
            epsilon = atof(options[EPSILON].arg);
        }
        if (options[MAXITER]) {
            maxIter = atoi(options[MAXITER].arg);
        }
        if (options[REGTYPE]) {
            regType = options[REGTYPE].arg;
        }
        HighOrderCRFProcessor proc;
        proc.train(filename, numThreads, maxIter, regType == "L1", coeff, epsilon);
        proc.writeModel(modelFilename);
        
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

        vector<string> seq;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) {
                future<vector<string>> f = (options[CALC_LIKELIHOOD] ? tq.enqueue(&HighOrderCRFProcessor::calcLabelLikelihoods, proc, seq) :
                    tq.enqueue(&HighOrderCRFProcessor::tag, proc, seq));
                futureQueue.push(move(f));
                if (numThreads == 1) {
                    futureQueue.front().wait();
                }
                while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    auto ret = futureQueue.front().get();
                    for (const auto &str : ret) {
                        cout << str << endl;
                    }
                    futureQueue.pop();
                }
                seq.clear();
            }
            else {
                seq.emplace_back(move(line));
            }
        }
    }
}

} // namespace HighOrderCRF
