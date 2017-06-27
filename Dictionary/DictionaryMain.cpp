#include "../optionparser/optionparser.h"
#include "../Utility/EncryptionUtil.h"
#include "SingleDictionary.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

using std::bind;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::function;
using std::ofstream;
using std::string;
using std::vector;

namespace Dictionary {

enum optionIndex { UNKNOWN, HELP, ENCRYPT, OUT };

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
    { ENCRYPT, 0, "e", "encrypt", Arg::None, "  -e, --encrypt  \tEncrypts the dictionary." },
    { OUT, 0, "o", "out", Arg::Required, "  -o, --out  <filename>\tDesignates the output file." },
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

    function<void(char *, size_t)> encrypt = nullptr;
    if (options[ENCRYPT]) {
        encrypt = &Utility::encrypt;
    }

    string outfile;
    if (options[OUT]) {
        outfile = options[OUT].arg;
    }
    else {
        cerr << "Output file not designated." << endl;
        option::printUsage(cout, usage);
        return 1;
    }

    ofstream os(outfile, std::ios::binary);
    if (!os.is_open()) {
        cerr << "Cannot open file: " << outfile << endl;
        return 1;
    }
    SingleDictionary::build(cin, os, encrypt);
    return 0;
}

}  // namespace Dictionary

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    return Dictionary::mainProc(argc, argv);
}
