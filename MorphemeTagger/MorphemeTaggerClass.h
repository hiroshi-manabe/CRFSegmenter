#ifndef MORPHEME_TAGGER_MORPHEME_TAGGER_CLASS_H_
#define MORPHEME_TAGGER_MORPHEME_TAGGER_CLASS_H_

#include "../MaxEnt/MaxEntProcessor.h"
#include "Dictionary.h"
#include "MorphemeTaggerOptions.h"

#include <memory>
#include <string>
#include <vector>

namespace MorphemeTagger {

using std::shared_ptr;
using std::string;
using std::vector;

class MorphemeTaggerClass {

public:
    MorphemeTaggerClass(const MorphemeTaggerOptions &taggerOptions);
    void train(const string &trainingFilename, const string &modelFilename);
    vector<vector<string>> tag(vector<string> sentence) const;
    void test(const string &testFilename) const;
    void readModel(const string &modelFilename);

private:
    shared_ptr<Dictionary> dictionary;
    shared_ptr<MaxEnt::MaxEntProcessor> maxEntProcessor;
    MorphemeTaggerOptions options;
};

}

#endif  // MORPHEME_TAGGER_MORPHEME_TAGGER_CLASS_H_
