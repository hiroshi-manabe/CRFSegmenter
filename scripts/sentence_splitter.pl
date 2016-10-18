#!/usr/bin/env perl

use strict;
use utf8;
use open IO => ':utf8';
use open ':std';

use Getopt::Long qw(:config posix_default no_ignore_case gnu_compat);
use IO::Handle;

my $opt_concat = 0;
my $opt_ignore_latin = 0;

GetOptions('concatenate' => \$opt_concat, 'ignore-latin' => \$opt_ignore_latin);

while (<STDIN>) {
    chomp;
    s/\t/ /g;
    my $is_first = 1;
    my $prev = "";
    while (s/^([\x20\xa0]?)(.)//) {
        my $sp = $1;
        my $ch = $2;
        
        my $print_sp = ($is_first or (not $opt_concat and $sp eq "\x20") or ($opt_concat and $sp ne "")) ? " " : "";
        
        my $correct_label =($is_first or ((not $opt_concat and $sp ne "") or $opt_concat and $sp eq " ")) ? "1" : "0";
        
        my $possible_labels = "0,1";
        if ($is_first) {
            $possible_labels = "1";
        }
        elsif (not $opt_concat and $sp eq "\x20") {
            $possible_labels = "1";
        }
        elsif ($opt_concat and $sp eq "") {
            $possible_labels = "0";
        }
        elsif (not $opt_concat and
               $opt_ignore_latin and
               $correct_label == "0" and
               (($prev =~ m{^\d$} and $ch =~ m{^\d$}) or
               ($prev =~ m{^\p{Latin}$} and $ch =~ m{^\p{Latin}$}))) {
            $possible_labels = "0";
        }

        print join("\t", $print_sp.$ch, $possible_labels, $correct_label)."\n";
        $is_first = 0;
        $prev = $ch;
    }
    print "\n";
    STDOUT->flush();
}
