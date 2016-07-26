#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../optionparser/optionparser.h"
#include "SegmenterDataConverter.h"
#include "TaggerDataConverter.h"

namespace DataConverter {

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::ifstream;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

enum optionIndex { UNKNOWN, HELP, TRAIN, SEGMENT, CONTAINS_SPACES, IS_TRAINING, TEST, MODEL, DICT, CHAR_N, CHAR_W, CHAR_L, TYPE_N, TYPE_W, TYPE_L, DICT_L, TAG, WORD_N, WORD_W, WORD_L };

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
    { WORD_N, 0, "", "wordn", Arg::Required, "  --wordn  <number>\tN-gram length of words. Defaults to 2." },
    { WORD_W, 0, "", "wordw", Arg::Required, "  --wordw  <number>\tWindow width for words. Defaults to 2." },
    { WORD_L, 0, "", "wordl", Arg::Required, "  --wordl  <number>\tMaximum label length of words. Defaults to 4." },
    { 0, 0, 0, 0, 0, 0 }
};

bool fileExists(const string &filename) {
    ifstream infile(filename.c_str());
    return infile.good();
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

    unordered_map<string, string> op;
    shared_ptr<DataConverterInterface> converter;
    if (options[SEGMENT]) {
        converter.reset(new SegmenterDataConverter());
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
    }
    else if (options[TAG]) {
        converter.reset(new TaggerDataConverter());
        if (options[DICT]) {
            op["dictionaryFilename"] = options[DICT].arg;
        }
        if (options[WORD_N]) {
            op["wordMaxNgram"] = atoi(options[CHAR_N].arg);
        }
        if (options[WORD_W]) {
            op["wordMaxWindow"] = atoi(options[CHAR_W].arg);
        }
        if (options[WORD_L]) {
            op["wordMaxLabelLength"] = atoi(options[CHAR_L].arg);
        }
    }
    converter->setOptions(op);

    while (true) {
        auto ret = converter->generateFeaturesFromStream(cin);
        if (cin.eof()) {
            break;
        }
        for (const auto &str : ret) {
            cout << str << endl;
        }
        cout << endl;
    }

    return 0;
}


}  // namespace DataConverter

int main(int argc, char **argv) {
    return DataConverter::mainProc(argc, argv);
}
