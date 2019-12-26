#!/usr/bin/env perl
use strict;

use File::Basename;
use FindBin;
use Getopt::Long qw(:config bundling posix_default no_ignore_case);

sub usage {
    print <<USAGE;
usage: $FindBin::Script --prefix <output file prefix> [-n|--normal-dict <path to a dictionary for indeclinable words]... [-d|--declinable-dict <path to a dictionary for declinable words]... [-c|--concat-dict <path to a concatenation dictionary]...
USAGE
    exit(0);
}

my %opts;
GetOptions(
    \%opts,
    "normal-dict|n=s@",
    "declinable-dict|d=s@",
    "concat-dict|c=s@",
    "prefix|p=s"
    );
my @required = qw(prefix);
usage() if grep { not exists $opts{$_}; } @required;

my $config_ref = {};
my $script_dir = dirname(__FILE__);
require "${script_dir}/analyze.config.pl";
config::get_config($config_ref);

my $src_dicts = join(" ", (map { "-n $_ "; } @{$opts{"normal-dict"}}), (map { "-d $_"; } @{$opts{"declinable-dict"}}), (map {"-c $_"; } @{$opts{"concat-dict"}}));

my $cmd = "$config_ref->{SCRIPT_DIR}/convert_japanese_dict_with_args.pl $src_dicts --prefix $opts{'prefix'} --convert-dict";

print STDERR $cmd."\n";
system($cmd);
