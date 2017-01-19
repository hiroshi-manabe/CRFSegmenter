#include "FileUtil.h"

#include <istream>
#include <string>
#include <vector>

using std::istream;
using std::string;
using std::vector;

namespace Utility {

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

}  // namespace Utility
