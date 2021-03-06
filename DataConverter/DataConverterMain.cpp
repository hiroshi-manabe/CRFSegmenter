#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../HighOrderCRF/DataSequence.h"
#include "../Utility/FileUtil.h"
#include "../Utility/StringUtil.h"
#include "SegmenterDataConverter.h"
#include "TaggerDataConverter.h"

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::queue;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace DataConverter {

enum optionIndex { UNKNOWN, HELP, THREADS, TRAIN, SEGMENT, CONTAINS_SPACES, IS_TRAINING, TEST, MODEL, DICT, CHAR_N, CHAR_W, CHAR_L, TYPE_N, TYPE_W, TYPE_L, DICT_L, TAG, WORD_N, WORD_W, WORD_L, CHAR, CHAR_TYPE };

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
    { DICT, 0, "", "dict", Arg::Required, "  --dict  <file>\t(Segmenter, Tagger)Designates the dictionary file to be loaded." },
    { CHAR_N, 0, "", "charn", Arg::Required, "  --charn  <number>\t(Segmentation) N-gram length of characters. Defaults to 3." },
    { CHAR_W, 0, "", "charw", Arg::Required, "  --charw  <number>\t(Segmentation) Window width for characters. Defaults to 3." },
    { CHAR_L, 0, "", "charl", Arg::Required, "  --charl  <number>\t(Segmentation) Maximum label length of characters. Defaults to 4." },
    { TYPE_N, 0, "", "typen", Arg::Required, "  --typen  <number>\t(Segmentation) N-gram length of character types. Defaults to 3." },
    { TYPE_W, 0, "", "typew", Arg::Required, "  --typew  <number>\t(Segmentation) Window width for character types. Defaults to 3." },
    { TYPE_L, 0, "", "typel", Arg::Required, "  --typel  <number>\t(Segmentation) Maximum label length of character types. Defaults to 1." },
    { DICT_L, 0, "", "dictl", Arg::Required, "  --dictl  <number>\t(Segmentation) Maximum label length of dictionary words. Defaults to 5." },
    { IS_TRAINING, 0, "", "training", Arg::None, "  --training  \t(Segmentation) Generates features for training." },
    { SEGMENT, 0, "", "segment", Arg::None, "  --segment  \tGenerates features for segmentation." },
    { CONTAINS_SPACES, 0, "", "contains-spaces", Arg::None, "  --contains-spaces  \t(Segmentation) Indicates that the original text contains spaces (e.g. Korean)." },
    { TAG, 0, "", "tag", Arg::None, "  --tag  \tGenerates features for tagging." },
    { WORD_N, 0, "", "wordn", Arg::Required, "  --wordn  <number>\t(Tagging) N-gram length of words. Defaults to 2." },
    { WORD_W, 0, "", "wordw", Arg::Required, "  --wordw  <number>\t(Tagging) Window width for words. Defaults to 2." },
    { WORD_L, 0, "", "wordl", Arg::Required, "  --wordl  <number>\t(Tagging) Maximum label length of words. Defaults to 4." },
    { CHAR, 0, "", "char", Arg::Required, "  --char  <number>\t(Tagging) Maximum length of word prefixes and suffixes to generate features." },
    { CHAR_TYPE, 0, "", "char-type", Arg::Required, "  --char-type  <number>\t(Tagging) Maximum length of character types of prefixes and suffixes to generate features." },
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
            option::printUsage(cerr, usage);
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
    
    unordered_map<string, string> op;
    unordered_set<string> dictionaries;
    shared_ptr<DataConverterInterface> converter;

    for (option::Option* opt = options[DICT]; opt; opt = opt->next()) {
        dictionaries.insert(opt->arg);
    }
    
    if (options[SEGMENT]) {
        if (options[CHAR_N]) {
            op["charMaxNgram"] = options[CHAR_N].arg;
        }
        if (options[CHAR_W]) {
            op["charMaxWindow"] = options[CHAR_W].arg;
        }
        if (options[CHAR_L]) {
            op["charMaxLabelLength"] = options[CHAR_L].arg;
        }
        if (options[TYPE_N]) {
            op["charTypeMaxNgram"] = options[TYPE_N].arg;
        }
        if (options[TYPE_W]) {
            op["charTypeMaxWindow"] = options[TYPE_W].arg;
        }
        if (options[TYPE_L]) {
            op["charTypeMaxLabelLength"] = options[TYPE_L].arg;
        }
        if (options[DICT_L]) {
            op["dictMaxLabelLength"] = options[TYPE_L].arg;
        }
        if (options[CONTAINS_SPACES]) {
            op["containsSpaces"] = "true";
        }
        converter.reset(new SegmenterDataConverter(op, dictionaries));
    }
    else if (options[TAG]) {
        if (options[WORD_N]) {
            op["wordMaxNgram"] = options[WORD_N].arg;
        }
        if (options[WORD_W]) {
            op["wordMaxWindow"] = options[WORD_W].arg;
        }
        if (options[WORD_L]) {
            op["wordMaxLabelLength"] = options[WORD_L].arg;
        }
        if (options[CHAR]) {
            op["characterLength"] = options[CHAR].arg;
        }
        if (options[CHAR_TYPE]) {
            op["characterTypeLength"] = options[CHAR_TYPE].arg;
        }
        converter.reset(new TaggerDataConverter(op, dictionaries));
    }
    else {
        cerr << "You must specify --segment or --tag option." << endl;
        option::printUsage(cerr, usage);
        return 1;
    }
    
    try {
        if (options[SEGMENT]) {
            converter.reset(new SegmenterDataConverter(op, dictionaries));
        }
        else if (options[TAG]) {
            converter.reset(new TaggerDataConverter(op, dictionaries));
        }
    }
    catch (std::invalid_argument) {
        cerr << "Invalid argument." << endl;
        option::printUsage(cerr, usage);
    }
    catch (std::out_of_range) {
        cerr << "Argument out of range." << endl;
        option::printUsage(cerr, usage);
    }


    hwm::task_queue tq(numThreads);
    queue<future<shared_ptr<HighOrderCRF::DataSequence>>> futureQueue;

    while (true) {
        auto seq = Utility::readSequence(cin);
        bool emptyFlag = seq.empty();
        future<shared_ptr<HighOrderCRF::DataSequence>> f = tq.enqueue(&DataConverterInterface::toDataSequence, converter.get(), seq);
        futureQueue.push(move(f));
        
        if ((numThreads == 1 || !cin) && !futureQueue.empty()) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto ret = futureQueue.front().get();
            futureQueue.pop();
            if (!(!cin && emptyFlag && futureQueue.empty())) {
                ret->write(cout);
            }
        }
        if (!cin && emptyFlag && futureQueue.empty()) {
            break;
        }
    }

    return 0;
}

}  // namespace DataConverter

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return DataConverter::mainProc(argc, argv);
}
