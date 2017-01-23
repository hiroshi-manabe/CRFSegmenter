#!/usr/bin/env perl

use strict;
use utf8;
use open IO => ':utf8';
use open ':std';

use Getopt::Long qw(:config posix_default no_ignore_case gnu_compat);
use IO::Handle;

my $opt_concat = 0;
my $opt_ignore_latin = 0;
my $opt_ignore_url = 0;
my $opt_ignore_numbers = 0;
my $preprocess = 0;

my $nonchar_base = 0xfdd0;
my $nonchar_code = -1;
my $nonchar = "\x{fdd0}";
my $nonchar_regex = qr{[\x{fd00}-\x{fdef}]};

sub rotate_nonchar {
    $nonchar_code = ($nonchar_code + 1) % 32;
    $nonchar = chr($nonchar_base + $nonchar_code);
}

sub to_hankaku {
    my $orig = shift;
    return join('', map { my $c = ord($_); ($c >= 0xff01 && $c <= 0xff5e) ? chr($c - 0xfee0) : $_; } split(//, $orig));
}

GetOptions('concatenate' => \$opt_concat,
           'ignore-latin' => \$opt_ignore_latin,
           'ignore-url' => \$opt_ignore_url,
           'ignore-numbers' => \$opt_ignore_numbers);

$preprocess = ($opt_ignore_url || $opt_ignore_numbers || $opt_ignore_latin);

while (<STDIN>) {
    chomp;
    s/\t/ /g;
    my $is_first = 1;
    my $prev = "";

    my $preprocessed = to_hankaku($_);
    if ($preprocess) {
        $preprocessed =~ s{([a-z]+://[~.!*'()A-Za-z0-9;/?:@&=+$,%#_]+)}{ rotate_nonchar(); $nonchar x length($1); }ge if $opt_ignore_url;
        $preprocessed =~ s{((?:mailto:)?[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~\-]+@[a-zA-Z0-9\-]+(?:.[a-zA-Z0-9\-]+)*)}{ rotate_nonchar(); $nonchar x length($1); }ge  if $opt_ignore_url;
        $preprocessed =~ s{([\d\.,]*[\d\.])}{ rotate_nonchar(); $nonchar x length($1); }ge if $opt_ignore_numbers;
        $preprocessed =~ s{([A-Za-z]+)}{ rotate_nonchar(); $nonchar x length($1); }ge if $opt_ignore_latin;
    }

    my $prev_preprocessed_char = '';
    while (s/^([\x20\xa0]?)(.)//) {
        my $sp = $1;
        my $ch = $2;
        $preprocessed =~ s/^[\x20\xa0]?(.)//;
        my $preprocessed_char = $1;
        
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
        elsif ($preprocess and
               ($prev_preprocessed_char =~ m{$nonchar_regex} or
                $preprocessed_char =~ m{$nonchar_regex})) {
            if ($prev_preprocessed_char eq $preprocessed_char) {
                $possible_labels = "0";
            }
            elsif ($prev_preprocessed_char =~ m{$nonchar_regex} and
                   $preprocessed_char =~ m{$nonchar_regex}) {
                $possible_labels = "1";
            }
            else {
                $possible_labels = "0,1";
            }
        }
        
        my %possible_label_dict = ();
        @possible_label_dict{split(/,/, $possible_labels)} = ();
        if (not exists $possible_label_dict{$correct_label}) {
            if ($preprocess) {
                $correct_label = (keys %possible_label_dict)[0];
            }
            else {
                die "Correct label ($correct_label) is not in possible labels ($possible_labels).";
            }
        }

        print join("\t", $print_sp.$ch, $possible_labels, $correct_label)."\n";
        $is_first = 0;
        $prev = $ch;
        $prev_preprocessed_char = $preprocessed_char;
    }
    print "\n";
    STDOUT->flush();
}
