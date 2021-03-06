CRFSegmenter
============

(English follows Japanese)

紹介
------------

**CRFSegmenter**は、[高次CRF](http://vocrf.net/docs/thesis_en.pdf)を利用した形態素解析器です。

モデルと辞書を含んでいるため、すぐに使い始めることができます。

必要なもの
------------

* CMake (>= 2.6)
* g++ または clang または Visual C++（C++11に対応したもの）

ビルド
------------

以下をプロジェクトディレクトリで実行します。

    $ ./scripts/set_build_dir.pl build/
    $ cd build/
    $ cmake ..
    $ make

実行・入出力
------------

以下をプロジェクトディレクトリで実行すると、標準入力から日本語文を読み込み、形態素列を出力します。文の終わりは空行で示されます。

    $ ./scripts/japanese.analyze.pl
    今日はいい天気ですね。
    今日	名詞-副詞可能	名詞-副詞可能	*	*	今日-キョウ	キョウ	    キョー	今日	キョウ	キョー
    は	助詞	助詞-係助詞	*	*	は-ハ	ハ	ワ	は	ハ	ワ
    いい	形容詞-自立	形容詞-自立	基本形	形容詞・イイ	いい-イイ	イイ	イイ	いい	イイ	イイ
    天気	名詞	名詞-一般	*	*	天気-テンキ	テンキ	テンキ	天気	テンキ	テンキ
    です	助動詞	助動詞	基本形	特殊・デス	です-デス	デス	デス	です	デス	デス
    ね	助詞	助詞-終助詞	*	*	ね-ネ	ネ	ネ	ね	ネ	ネ
    。	記号-句点	記号-句点	*	*	。-*	*	*	。	*	*

形態素列のフォーマットはタブ区切りテキストで、左から順に

- 表記
- 簡易品詞（resources/pos_table_ipadic.tsv 2列目に記載）
- 品詞（resources/pos_table_ipadic.tsv 1列目に記載）
- （用言のみ）活用形（resources/cforms.tsv 2列目に記載）
- （用言のみ）活用タイプ（resources/cforms.tsv 1列目に記載）
- 代表形（「表記-読み」形式）
- 読み
- 発音
- 原形表記（非用言の場合、表記と同じ）
- 原形読み（非用言の場合、読みと同じ）
- 原形発音（非用言の場合、発音と同じ）

となります。

ユーザー辞書
------------

ユーザー辞書のフォーマットはタブ区切りテキストで、左から順に

- 読み
- 発音
- 品詞（resources/pos_table_ipadic.tsv 1列目に記載）
- 活用タイプ（resources/cforms.tsv 1列目に記載。非用言の場合は"*"）
- 表記
- 代表形（「表記-読み」形式）

となります。

ユーザー辞書を使う前に、プログラムから使用可能な形に変換する必要があります。

変換は以下のようにします。

    $ ./script/convert_japanese_dict.pl --prefix <出力ファイル名> [-d 辞書]...

-d は複数指定可能です。

--prefix で指定したファイル名に .segment, .postag, .morph という拡張子が追加されたファイルがそれぞれ生成されます。

ユーザー辞書を使って形態素解析を行う場合は、次のようにします。

    $ ./script/japanese.analyze.pl --user-dict-prefix <ユーザーファイル名>

この場合も、--user-dict-prefix で指定したファイル名に .segment, .postag, .morph という拡張子が追加されたファイルがそれぞれ読み込まれます。

What's this?
------------

**CRFSegmenter** is an implementation of [high-order CRF](http://vocrf.net/docs/thesis_en.pdf) paired with utility programs that facilitate word segmentation and POS-tagging.

It also contains a morphological disambiguator (maximum-entropy-based).

Requirements
------------

* CMake (>= 2.6)
* g++, clang or Visual C++ with C++11 support

How to build the executables
----------------------------
    $ cmake
    $ make

The executables will be generated in their directories (DataConverter, HighOrderCRF and MorphemeTagger).

How to use
----------

All data must be encoded in UTF-8.

### Word segmentation

#### Data Format

Training data should be separated with non-breaking spaces (\xa0), like:

    今天[\xa0]天气[\xa0]很[\xa0]好 。[LF]

Input data for segmentations is a plain text, like:

    今天天气很好。[LF]

Output data will be separated with spaces (\x20) and not non-breaking spaces (\xa0). The (ideal) result for the data above will be like:

    今天 天气 很 好 。[LF]

#### Dictionary Format

A source dictionary file should be in tab-separated form, like:

    天气[TAB]LEN:2[TAB]POS:NN[TAB]...[LF]
    好[TAB]LEN:1[TAB]POS:JJ[TAB]...[LF]
    ....

The first column should contain words. You can add an arbitrary number of features in other columns, but the number of columns should be consistent throughout the file.

You have to convert source dictionary files into the binary format to be used by the program as follows:

    ./Dictionary/DictionaryMain -o <output dictionary> < <source dictionary>

#### Training

    cat <input file> | ./scripts/sentence_splitter.pl | ./DataConverter/DataConverterMain --segment [--dict <dictionary file] > <temporary file>
    ./HighOrderCRF/HighOrderCRFMain --train <temporary file> --model <model file> --c1 <L1 regularization coefficient> --c2 <L2 regularization coefficient>

If you omit both ```--c1``` and ```c2```, L1 regularization coefficient will be set to 0.05 and L2 regularization coefficient will be set to 0.

#### Performing segmentation

    cat <input file> | ./scripts/sentence_splitter.pl [--ignore-latin] | ./DataConverter/DataConverterMain --segment [--dict <dictionary file>] | ./HighOrderCRF/HighOrderCRFMain --tag --model <model file> | ./scripts/sentence_joiner.pl

If you use --ignore-latin option, the result will never be split between latin characters, which is often the desired behavior when processing CJK texts.

### POS-tagging

#### Data Format

Each line of training data should be a word and its POS-tag (tab-separated). Sentences should be separated with an empty line.

Training Data will look like:

    time[TAB]NN[LF]
    flies[TAB]VBS[LF]
    like[TAB]IN[LF]
    an[TAB]DT[LF]
    arrow[TAB]NN[LF]
    .[TAB].[LF]
    [LF]
    ...

Input data for POS-tagging only contains one word in each line.

    time[LF]
    flies[LF]
    like[LF]
    an[LF]
    arrow[LF]
    .[LF]
    [LF]
    ...

Output data format is the same as that of training data.

    time[TAB]NN[LF]
    flies[TAB]VBS[LF]
    like[TAB]IN[LF]
    an[TAB]DT[LF]
    arrow[TAB]NN[LF]
    .[TAB].[LF]
    [LF]
    ...

#### Dictionary Format

The dictionary file should list words and their possible tags, like in the following example:

    time[TAB]NN
    time[TAB]VB
    flies[TAB]NNS
    files[TAB]VBS
    ...

"Possible tags" means the tags with which the word is tagged. In the above example, the word "time" will always be tagged with NN or VB and never with NNS or VBS.

You have to convert source dictionary files into the binary format to be used by the program as follows:

    ./Dictionary/DictionaryMain -o <output dictionary> < <source dictionary>

#### Training

    cat <input file> | ./DataConverter/DataConverterMain --tag [--dict <dictionary file] > <temporary file>
    ./HighOrderCRF/HighOrderCRFMain --train <temporary file> --model <model file>  --c1 <L1 regularization coefficient> --c2 <L2 regularization coefficient>
    
If you omit both ```--c1``` and ```c2```, L1 regularization coefficient will be set to 0.05 and L2 regularization coefficient will be set to 0.

#### Performing POS-tagging

    cat <input file> | ./DataConverter/DataConverterMain --tag [--dict <dictionary file] | ./HighOrderCRF/HighOrderCRFMain --tag --model <model file>

### Directly using high-order CRF

#### Data Format

Input data should follow the following format:

    <Sentence 1 line 1>[LF]
    <Sentence 1 line 2>[LF]
    ...
    <Sentence 1 line k>[LF]
    [LF]
    <Sentence 2 line 1>[LF]
    <Sentence 2 line 2>[LF]
    ...
    <Sentence 2 line l>[LF]
    [LF]
    ...
    <Sentence n line 1>[LF]
    <Sentence n line 2>[LF]
    ...
    <Sentence n line m>[LF]
    [LF]

Each line of input data should follow the following format:

    <Original text>[TAB]<Possible labels>[TAB]<Correct label>[TAB]<Feature 1 label length:Feature 1 string>[TAB]<Feature 2 label length:Feature 2 string>...[LF]

```<Original text>``` field is not used in tagging.

Below are some example data.

    time	VB,NN	NN	1:*	1:W+0/time	1:W+0/time_flies	1:C+1/t	1:C+2/ti	1:C-1/e	1:C-2/me	1:T+1/LATIN	1:T+2/LATIN_LATIN	1:T-1/LATIN	1:T-2/LATIN_LATIN	1:D-NN	1:D-VB
    flies	VBS,NNS	VBS	1:*	2:*	1:W-1/time	2:W-1/time	1:W-1/time_flies	2:W-1/time_flies	1:W+0/flies	1:W+0/flies_like	1:C+1/f	1:C+2/fl	1:C-1/s	1:C-2/es	1:T+1/LATIN	1:T+2/LATIN_LATIN	1:T-1/LATIN	1:T-2/LATIN_LATIN	1:D-NNS	1:D-VBS
    like	VB,IN	IN	1:*	2:*	1:W-2/time_flies	2:W-2/time_flies	3:W-2/time_flies	1:W-1/flies	2:W-1/flies	1:W-1/flies_like	2:W-1/flies_like	1:W+0/like	1:W+0/like_an	1:C+1/l	1:C+2/li	1:C-1/e	1:C-2/ke	1:T+1/LATIN	1:T+2/LATIN_LATIN	1:T-1/LATIN	1:T-2/LATIN_LATIN	1:D-IN	1:D-VB
    an	DT	DT	1:*	2:*	1:W-2/flies_like	2:W-2/flies_like	3:W-2/flies_like	1:W-1/like	2:W-1/like	1:W-1/like_an	2:W-1/like_an	1:W+0/an	1:W+0/an_arrow	1:C+1/a	1:C+2/an	1:C-1/n	1:C-2/an	1:T+1/LATIN	1:T+2/LATIN_LATIN	1:T-1/LATIN	1:T-2/LATIN_LATIN	1:D-DT
    arrow	NN	*	1:*	2:*	1:W-2/like_an	2:W-2/like_an	3:W-2/like_an	1:W-1/an	2:W-1/an	1:W-1/an_arrow	2:W-1/an_arrow	1:W+0/arrow	1:W+0/arrow_.	1:C+1/a	1:C+2/ar	1:C-1/w	1:C-2/ow	1:T+1/LATIN	1:T+2/LATIN_LATIN	1:T-1/LATIN	1:T-2/LATIN_LATIN	1:D-NN
    .	.	.	1:*	2:*	1:W-2/an_arrow	2:W-2/an_arrow	3:W-2/an_arrow	1:W-1/arrow	2:W-1/arrow	1:W-1/arrow_.	2:W-1/arrow_.	1:W+0/.	1:C+1/.	1:C-1/.	1:T+1/COMMON	1:T-1/COMMON	1:D-.

Each line of output data will be in the following format:

    <Original text>[TAB]<Inferred label>

Training:

    ./HighOrderCRF/HighOrderCRFMain --train <training data> --model <model output file>  --c1 <L1 regularization coefficient> --c2 <L2 regularization coefficient>

If you omit both ```--c1``` and ```c2```, L1 regularization coefficient will be set to 0.05 and L2 regularization coefficient will be set to 0.

Tagging:

    cat <input file> | ./HighOrderCRF/HighOrderCRFMain --tag --model <model file>
