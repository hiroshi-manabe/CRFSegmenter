#!/usr/bin/env perl
use strict;

use utf8;
use open IO => ':utf8';
use open ':std';

use File::Basename;
use Getopt::Long qw(:config bundling posix_default no_ignore_case);
use List::Util qw(max min);

my %opts;
GetOptions(
    \%opts,
    'data-dir=s'
    );
my $config_ref = { "ROOT_DIR" => $opts{"data-dir"} };

my $script_dir = dirname(__FILE__);
require "${script_dir}/analyze.config.pl";
config::get_config($config_ref);

$| = 1;
my %dict = ();
my $node = \%dict;
open IN, "<", "$config_ref->{JAPANESE_POSTPROCESS_FILE}";
while (<IN>) {
    chomp;
    my $flag = s/^>//;
    if ($flag) {
        $node->{"END"} = $_;
        $node = \%dict;
    }
    else {
        $node->{$_} = {} if not exists $node->{$_};
        $node = $node->{$_};
    }
}
close IN;

my @nakaguro_result = qw(記号-一般 記号-一般 * * ・-* * * ・ * *);

my @sent_split;
$node = \%dict;
my $node_count = 0;
my $symbol_count = 0;
my $max_merge_count = 7;

while (<>) {
    chomp;
    my @F = split /\t/, $_;

    if (exists $node->{$_}) {
        $node = $node->{$_};
        $node_count++;
    }
    else {
        if ($node_count and exists $node->{"END"}) {
            splice @sent_split, -$node_count, $node_count, [split/\t/, $node->{"END"}];
        }
        $node = \%dict;
        $node_count = 0;
    }

    if (@sent_split and scalar(@{$sent_split[-1]}) == 2 and $sent_split[-1]->[0] =~ m{^(.*[\p{Katakana}ー]・[\p{Katakana}ー].*)$}) {
        my @split = split /(?<=[\p{Katakana}ー])(・)(?=[\p{Katakana}ー])/, $sent_split[-1]->[0];
        splice @sent_split, -1, 1, map { [$_, $_ eq "・" ? @nakaguro_result : "名詞" ]; } @split;
        $node = \%dict;
        $node_count = 0;
    }

    if (not $_) {
        if (@sent_split) {
            for my $line(@sent_split) {
                print join("\t", @{$line})."\n";
            }
        }
        print "\n";
        @sent_split = ();
    }
    else {
        push @sent_split, [@F];
    }
}
