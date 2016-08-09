#!/usr/bin/env perl

use strict;
use utf8;
use open IO => ':utf8';
use open ':std';
use Getopt::Long;

$| = 1;

my $opt_newline = 0;

GetOptions('newline' => \$opt_newline);

my $delim = $opt_newline ? "\n" : " ";

my $sentence = '';
my $is_first = 1;
while (<STDIN>) {
    chomp;
    if ($_ eq '') {
        $sentence .= $delim if $opt_newline;
        print $sentence."\n";
        $sentence = '';
        $is_first = 1;
    }
    else {
        my @F = split /\t/, $_;
        $F[0] =~ s/^ //;
        $sentence .= $delim if $F[1] eq "1" and not $is_first;
        $sentence .= $F[0];
        $is_first = 0;
    }
}
