CRFSegmenter
============

What's this?
------------

**CRFSegmenter** is a high-order-CRF-based multi-language text segmenter.

It also contains a POS tagger (high-order-CRF-based) and morphological disambiguator (maximum-entropy-based).

Requirements
------------

* CMake (>= 2.6)
* g++, clang or Visual C++ with C++11 support

How to build the executables
----------------------------
    $ cmake
    $ make

The executables will be generated in their directories (Segmenter, Tagger, MorphemeTagger).

How to use
----------

###Segmenter

####Commands

Training:

    ./Segmenter/Segmenter --train <training data file> --model <model file> [--dict <dictionary file>] --regtype L1 --coeff 0.05
    
Test:

    ./Segmenter/Segmenter --test <test data file> --model <model file> [--dict <dictionary file>]

Segmentation:

    ./Segmenter/Segmenter --segment --model <model file> [--dict <dictionary file] < <input file> > <output file>

For more details, please type `./Segmenter/Segmenter --help`.

####Text file format

The training file is a space-separated plain text file, like:

    This is an example .

The input file is a text file before segmentation, like:

    Thisisanexample.

The training / input files must be encoded in UTF-8.

####Dictionary file format

The dictionary file is a tab-separated plain text file with one or more features, like:

    word1[TAB]feature1-1[TAB]feature2-1
    word2[TAB]feature1-2[TAB]feature2-2
    ...

The number of columns must be consistent throughout the file.

###POS Tagger

####Commands

Training:

    ./Tagger/Tagger --train <training data file> --tagset <tag set file> --model <model file> [--dict <dictionary file>] --regtype L1 --coeff 0.05
    
Test:

    ./Tagger/Tagger --test <test data file> --model <model file> [--dict <dictionary file>]

Tagging:

    ./Tagger/Tagger --tag --model <model file> [--dict <dictionary file] [--newline] < <input file> > <output file>

For more details, please type `./Tagger/Tagger --help`.

####Text file format

The training file should contain space-separated words with POS tags, like:

     This/DT is/VBZ an/DT example/NN ./.

The input file should contain space-separated words like:

    This is an example .

The output file is basically in the same format as the training file, but you can make it newline-separated by using `--newline` option. This way, you can pass it to the morphological disambiguator.

####Tag set file format

The tag set file is a text file in which each line contains a tag used in the training file, like:

    CC
    CD
    DT
    ...

####Dictionary format

The dictionary file should list words and their possible tags like in the following example:

    time[TAB]NN
    time[TAB]VB
    flies[TAB]NNS
    files[TAB]VBS
    ...

###Morphological Disambiguator

####Commands

Training:

    ./MorphemeTagger/MorphemeTagger --train <training data file> --model <model file> [--fcolumns <comma-separated numbers>] [--dict <dictionary file>] --regtype L1 --coeff 0.05

Test:

    ./MorphemeTagger/MorphemeTagger --test <test data file> --model <model file> [--dict <dictionary file>]

Tagging:

    ./MorphemeTagger/MorphemeTagger --tag --model <model file> [--dict <dictionary file] < <input file> > <output file>
