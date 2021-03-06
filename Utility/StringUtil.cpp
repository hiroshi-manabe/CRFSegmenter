#include "StringUtil.h"

#include <string>
#include <sstream>
#include <vector>

using std::getline;
using std::string;
using std::stringstream;
using std::vector;

namespace Utility {

vector<string> splitString(const string &s, char delim, int count) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    int i = 1;
    while (getline(ss, item, (count && i >= count) ? '\0' : delim)) {
        elems.emplace_back(item);
        ++i;
    }
    return elems;
}

vector<string> rsplit2(const string &s, char delim) {
    vector<string> elems;
    size_t pos = s.rfind(delim);
    elems.emplace_back(s.substr(0, pos));
    if (pos != string::npos) {
        elems.emplace_back(s.substr(pos + 1));
    }
    return elems;
}

string join(const vector<string> &v, char delim) {
    bool isFirst = true;
    string ret;
    for (const auto &s : v) {
        if (!isFirst) {
            ret += delim;
        }
        ret.append(s);
        isFirst = false;
    }
    return ret;
}

}  // namespace Utility
