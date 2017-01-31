#include "MorphemeDisambiguatorClass.h"

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../Utility/FileUtil.h"
#include "../Utility/StringUtil.h"
#include "MorphemeDisambiguatorOptions.h"

#include <chrono>
#include <future>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace MorphemeDisambiguator {

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::future;
using std::move;
using std::queue;
using std::string;
using std::vector;

enum optionIndex { UNKNOWN, HELP, TRAIN, TAG, TEST, MODEL, DICT, THREADS, WORD_W, LABEL_W, COLUMN_W, FCOLUMN, C1, C2, EPSILON, MAXITER };

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
    { WORD_W, 0, "", "wordw", Arg::Required, "  --wordw  <number>\tWindow width for words." },
    { LABEL_W, 0, "", "labelw", Arg::Required, "  --labelw  <number>\tWindow width for words." },
    { COLUMN_W, 0, "", "columnw", Arg::Required, "  --columnw  <number>\tWindow width for columns." },
    { FCOLUMN, 0, "", "fcolumn", Arg::Required, "  --fcolumn  <number>\tDesignates the column to use as features." },
    { TAG, 0, "", "tag", Arg::None, "  --tag  \tTags the text read from the standard input and writes the result to the standard output. This option can be omitted." },
    { TEST, 0, "", "test", Arg::Required, "  --test  <file>\tTests the model with the given file." },
    { TRAIN, 0, "", "train", Arg::Required, "  --train  <file>\tTrains the model on the given file." },
    { C1, 0, "", "c1", Arg::Required, "  --c1  <number>\t(For training) Sets the coefficient for L1 regularization. The default value is 0.05 (defaults to 0 if the c2 is explicitly set)." },
    { C2, 0, "", "c2", Arg::Required, "  --c2  <number>\t(For training) Sets the coefficient for L2 regularization. The default value is 0 (no L2 regularization)." },
    { EPSILON, 0, "", "epsilon", Arg::Required, "  --epsilon  <number>\tSets the epsilon for convergence." },
    { MAXITER, 0, "", "maxiter", Arg::Required, "  --maxiter  <number>\tSets the maximum iteration count." },
    { THREADS, 0, "", "threads", Arg::Required, "  --threads  <number>\tDesignates the number of threads to run concurrently." },
    { 0, 0, 0, 0, 0, 0 }
};

int mainProc(int argc, char **argv) {
    MorphemeDisambiguator::MorphemeDisambiguatorOptions op = { 2, 1, 1 };

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

    string modelFilename;
    if (options[MODEL]) {
        modelFilename = options[MODEL].arg;
    }
    else {
        option::printUsage(cerr, usage);
        return 0;
    }

    for (option::Option* opt = options[DICT]; opt; opt = opt->next()) {
        op.dictionaries.insert(opt->arg);
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

    if (options[WORD_W]) {
        op.wordMaxWindow = atoi(options[WORD_W].arg);
    }
    if (options[LABEL_W]) {
        op.labelMaxWindow = atoi(options[LABEL_W].arg);
    }
    if (options[COLUMN_W]) {
        op.columnMaxWindow = atoi(options[COLUMN_W].arg);
    }
    for (option::Option* opt = options[FCOLUMN]; opt; opt = opt->next()) {
        op.featureColumnSet.insert((size_t)atoi(opt->arg));
    }
        
    if (options[TRAIN]) {
        string trainingFilename = options[TRAIN].arg;
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
        
        MorphemeDisambiguator::MorphemeDisambiguatorClass s(op);

        s.train(trainingFilename, numThreads, maxIter, c1, c2, epsilon, modelFilename);
        return 0;
    }

    if (options[TEST]) {
        string testFilename = options[TEST].arg;
        MorphemeDisambiguator::MorphemeDisambiguatorClass s(op);
        s.readModel(modelFilename);
        s.test(testFilename);
        return 0;
    }

    // tags the inputs
    MorphemeDisambiguator::MorphemeDisambiguatorClass s(op);
    s.readModel(modelFilename);
    
    string line;
    hwm::task_queue tq(numThreads);
    queue<future<vector<vector<string>>>> futureQueue;

    while (true) {
        auto seq = Utility::readSequence(cin);
        bool emptyFlag = seq.empty();
        auto f = tq.enqueue(&MorphemeDisambiguator::MorphemeDisambiguatorClass::tag, &s, seq);
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

}  // namespace MorphemeDisambiguator

int main(int argc, char **argv) {
    return MorphemeDisambiguator::mainProc(argc, argv);
}

