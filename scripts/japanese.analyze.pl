#!/usr/bin/env perl
use strict;

use File::Basename;
use Getopt::Long qw(:config bundling posix_default no_ignore_case);

my %opts;
GetOptions(
    \%opts,
    'debug',
    'user-dict-prefix=s@',
    'data-dir=s',
    'threads=i'
    );
my $config_ref = { "ROOT_DIR" => $opts{"data-dir"} };

my $script_dir = dirname(__FILE__);
require "${script_dir}/analyze.config.pl";
config::get_config($config_ref);

my $segmenter_dict = $config_ref->{"JAPANESE_SEGMENTER_DICT"};
my $postag_dict = $config_ref->{"JAPANESE_POSTAG_DICT"};
my $morph_dict = $config_ref->{"JAPANESE_MORPHEME_DISAMBIGUATOR_DICT"};
my $concat_dict = $config_ref->{"JAPANESE_MORPHEME_CONCATENATOR_DICT"};

my $threads_str = '';
if ($opts{'threads'}) {
    $threads_str = "--threads $opts{threads}";
}

my $user_dict_str = join(" ", (map { "--segmenter-dict ${_}$config_ref->{JAPANESE_SEGMENTER_DICT_EXT} --tagger-dict ${_}$config_ref->{JAPANESE_POSTAG_DICT_EXT} --morph-dict ${_}$config_ref->{JAPANESE_MORPHEME_DISAMBIGUATOR_DICT_EXT}  --concat-dict ${_}$config_ref->{JAPANESE_MORPHEME_CONCATENATOR_DICT_EXT}"; } @{$opts{"user-dict-prefix"}}));

my $cmd;

$cmd = "$config_ref->{JAPANESE_ANALYZER_COMMAND} --segmenter-dict $config_ref->{JAPANESE_SEGMENTER_DICT} --tagger-dict $config_ref->{JAPANESE_POSTAG_DICT} --morph-dict $config_ref->{JAPANESE_MORPHEME_DISAMBIGUATOR_DICT} --concat-dict $config_ref->{JAPANESE_MORPHEME_CONCATENATOR_DICT} --segmenter-model $config_ref->{JAPANESE_SEGMENTER_MODEL} --tagger-model $config_ref->{JAPANESE_POSTAG_MODEL} --morph-model $config_ref->{JAPANESE_MORPHEME_DISAMBIGUATOR_MODEL} $user_dict_str $threads_str ";

$cmd .= "| $config_ref->{SCRIPT_DIR}/japanese_postprocess.pl";
print STDERR $cmd."\n" if exists $opts{"debug"};
system($cmd);
