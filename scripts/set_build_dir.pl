#!/usr/bin/env perl

use strict;
use Cwd;
use File::Basename;
use File::Spec;

my $cur_dir = dirname(__FILE__);

my $build_dir = shift;

if (not -d $build_dir) {
    mkdir $build_dir or die "Cannot create directory: $build_dir";
}
my $build_dir_abs = File::Spec->rel2abs(Cwd::realpath($build_dir));

open OUT, ">", "$cur_dir/build_dir.txt";
print OUT "$build_dir_abs\n";
close OUT;

my $project_dir_abs = File::Spec->rel2abs(Cwd::realpath($cur_dir."/.."));

print qq{cd to $build_dir and execute "cmake $project_dir_abs" and "make".\n"};
