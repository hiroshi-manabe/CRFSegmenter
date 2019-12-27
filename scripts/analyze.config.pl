#!/usr/bin/env perl

package config;
use strict;

use File::Basename;

sub get_config {
    my ($config_ref) = @_;
    $config_ref->{"SCRIPT_DIR"} = dirname(__FILE__);
    
    open IN, "<", "$config_ref->{SCRIPT_DIR}/build_dir.txt" or die "build_dir.txt not generated.";
    my $t = <IN>;
    chomp $t;
    close IN;
    $config_ref->{"BIN_DIR"} = $t."/bin";
    
    $config_ref->{"ROOT_DIR"} = "$config_ref->{SCRIPT_DIR}/..";
    $config_ref->{"MODEL_DIR"} = "$config_ref->{ROOT_DIR}/models";
    $config_ref->{"RESOURCE_DIR"} = "$config_ref->{ROOT_DIR}/resources";

    $config_ref->{"CFORMS_FILE"} = "$config_ref->{RESOURCE_DIR}/cforms.tsv";
    $config_ref->{"POS_TABLE_FILE"} = "$config_ref->{RESOURCE_DIR}/pos_table_ipadic.tsv";

    $config_ref->{"SENTENCE_SPLITTER"} = "$config_ref->{SCRIPT_DIR}/sentence_splitter.pl";
    $config_ref->{"SENTENCE_JOINER"} = "$config_ref->{SCRIPT_DIR}/sentence_joiner.pl";

    $config_ref->{"DATA_CONVERTER"} = "$config_ref->{BIN_DIR}/DataConverterMain";
    $config_ref->{"HOCRF"} = "$config_ref->{BIN_DIR}/HighOrderCRFMain";
    $config_ref->{"MORPHEME_DISAMBIGUATOR"} = "$config_ref->{BIN_DIR}/MorphemeDisambiguatorMain";
    $config_ref->{"MORPHEME_CONCATENATOR"} = "$config_ref->{BIN_DIR}/MorphemeConcatenatorMain";
    $config_ref->{"DICTIONARY_CONVERTER"} = "$config_ref->{BIN_DIR}/DictionaryMain";

    $config_ref->{"JAPANESE_SEGMENTER_DICT"} = "$config_ref->{MODEL_DIR}/japanese.dict.segment";
    $config_ref->{"JAPANESE_SEGMENTER_DICT_EXT"} = ".segment";
    $config_ref->{"JAPANESE_SEGMENTER_MODEL"} = "$config_ref->{MODEL_DIR}/japanese.segment.train.model";

    $config_ref->{"JAPANESE_POSTAG_DICT"} = "$config_ref->{MODEL_DIR}/japanese.dict.postag";
    $config_ref->{"JAPANESE_POSTAG_DICT_EXT"} = ".postag";
    $config_ref->{"JAPANESE_POSTAG_MODEL"} = "$config_ref->{MODEL_DIR}/japanese.postag.train.model";

    $config_ref->{"JAPANESE_MORPHEME_DISAMBIGUATOR_DICT"} = "$config_ref->{MODEL_DIR}/japanese.dict.morph";
    $config_ref->{"JAPANESE_MORPHEME_DISAMBIGUATOR_DICT_EXT"} = ".morph";
    $config_ref->{"JAPANESE_MORPHEME_DISAMBIGUATOR_MODEL"} = "$config_ref->{MODEL_DIR}/japanese.morph.train.model";

    $config_ref->{"JAPANESE_MORPHEME_DISAMBIGUATOR_COMMAND"} = "$config_ref->{MORPHEME_DISAMBIGUATOR} --tag --fcolumn 0 --fcolumn 3";

    $config_ref->{"JAPANESE_MORPHEME_CONCATENATOR_DICT"} = "$config_ref->{MODEL_DIR}/japanese.dict.concat";
    $config_ref->{"JAPANESE_MORPHEME_CONCATENATOR_DICT_EXT"} = ".concat";
    $config_ref->{"JAPANESE_MORPHEME_CONCATENATOR_COMMAND"} = "$config_ref->{MORPHEME_CONCATENATOR}";


    $config_ref->{"JAPANESE_ANALYZER_COMMAND"} = "$config_ref->{BIN_DIR}/JapaneseAnalyzerMain";
}
1;
