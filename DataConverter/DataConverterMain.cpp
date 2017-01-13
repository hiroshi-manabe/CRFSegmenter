#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../optionparser/optionparser.h"
#include "../task/task_queue.hpp"
#include "../HighOrderCRF/DataSequence.h"
#include "SegmenterDataConverter.h"
#include "TaggerDataConverter.h"

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::future;
using std::getline;
using std::istream;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

namespace DataConverter {

vector<string> splitString(const string &s, char delim = '\t', int count = 0) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    int i = 1;
    while (getline(ss, item, (count && i >= count) ? '\0' : delim)) {
        elems.push_back(item);
        ++i;
    }
    return elems;
}

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

vector<string> readSequence(istream &is) {
    vector<string> ret;
    string line;
    bool isOK = false;
    while (getline(is, line)) {
        if (line.empty()) {
            isOK = true;
            break;
        }
        ret.emplace_back(move(line));
    }
    if (!isOK) {
        ret.clear();
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
    shared_ptr<DataConverterInterface> converter;
    if (options[SEGMENT]) {
        auto c = new SegmenterDataConverter();
        if (options[DICT]) {
            op["dictionaryFilename"] = options[DICT].arg;
        }
        if (options[CHAR_N]) {
            op["charMaxNgram"] = atoi(options[CHAR_N].arg);
        }
        if (options[CHAR_W]) {
            op["charMaxWindow"] = atoi(options[CHAR_W].arg);
        }
        if (options[CHAR_L]) {
            op["charMaxLabelLength"] = atoi(options[CHAR_L].arg);
        }
        if (options[TYPE_N]) {
            op["charMaxNgram"] = atoi(options[TYPE_N].arg);
        }
        if (options[TYPE_W]) {
            op["charMaxWindow"] = atoi(options[TYPE_W].arg);
        }
        if (options[TYPE_L]) {
            op["charMaxLabelLength"] = atoi(options[TYPE_L].arg);
        }
        if (options[DICT_L]) {
            op["dictMaxLabelLength"] = atoi(options[TYPE_L].arg);
        }
        if (options[CONTAINS_SPACES]) {
            op["containsSpaces"] = "true";
        }
        c->setOptions(op);
        converter.reset(c);
    }
    else if (options[TAG]) {
        auto c = new TaggerDataConverter();
        if (options[DICT]) {
            op["dictionaryFilename"] = options[DICT].arg;
        }
        if (options[WORD_N]) {
            op["wordMaxNgram"] = atoi(options[WORD_N].arg);
        }
        if (options[WORD_W]) {
            op["wordMaxWindow"] = atoi(options[WORD_W].arg);
        }
        if (options[WORD_L]) {
            op["wordMaxLabelLength"] = atoi(options[WORD_L].arg);
        }
        if (options[CHAR]) {
            op["characterLength"] = atoi(options[CHAR].arg);
        }
        if (options[CHAR_TYPE]) {
            op["characterTypeLength"] = atoi(options[CHAR_TYPE].arg);
        }
        c->setOptions(op);
        converter.reset(c);
    }
    else {
        cerr << "You must specify --segment or --tag option." << endl;
        option::printUsage(cout, usage);
        return 1;
    }

    hwm::task_queue tq(numThreads);
    queue<future<shared_ptr<HighOrderCRF::DataSequence>>> futureQueue;

    while (true) {
        auto seq = readSequence(cin);
        if (seq.empty()) {
            break;
        }
        future<shared_ptr<HighOrderCRF::DataSequence>> f = tq.enqueue(&DataConverterInterface::toDataSequence, converter.get(), seq);
        futureQueue.push(move(f));
        if (numThreads == 1) {
            futureQueue.front().wait();
        }
        while (!futureQueue.empty() && futureQueue.front().wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto ret = futureQueue.front().get();
            ret->write(cout);
            futureQueue.pop();
        }
    }

    return 0;
}

}  // namespace DataConverter

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return DataConverter::mainProc(argc, argv);
}
