#!/usr/bin/env perl
use strict;

use utf8;
use Encode;
use open IO => ':utf8';
use open ':std';
use FindBin;
use lib $FindBin::Bin;
use AbgdData;
use FileHandle qw();

use Getopt::Long qw(:config posix_default no_ignore_case gnu_compat);

my $opt_concat = 0;
my $opt_ignore_latin = 0;
my $opt_ignore_url = 0;
my $opt_ignore_numbers = 0;
my $opt_decompose_html_tags = 0;
my $opt_convert_han_zen = 0;
my $preprocess = 0;

my $nonchar_base = 0xff000;
my $nonchar_num = 0xfffe;
my $nonchar_code = -1;
my $nonchar_range = chr($nonchar_base)."-".chr($nonchar_base + $nonchar_num - 1);

sub get_next_nonchar {
    $nonchar_code = ($nonchar_code + 1) % $nonchar_num;
    return chr($nonchar_base + $nonchar_code);
}

sub to_hankaku {
    return han_zen_converter($_[0], 0);
}

sub to_zenkaku {
    return han_zen_converter($_[0], 1);
}

sub han_zen_converter {
    my ($orig, $to_zenkaku) = @_;
    return join('', map { my $c = ord($_); $to_zenkaku ? ($c == 0x22 ? "\x{201c}" : (($c >= 0x21 && $c <= 0x7e) ? chr($c + 0xfee0) : $_)) : ((($c >= 0xff01 && $c <= 0xff5e) ? chr($c - 0xfee0) : $_)); } split(//, $orig));
}

GetOptions('concatenate' => \$opt_concat,
           'convert-han-zen', \$opt_convert_han_zen,
           'ignore-latin' => \$opt_ignore_latin,
           'ignore-url' => \$opt_ignore_url,
           'decompose-html-tags' => \$opt_decompose_html_tags,
           'ignore-numbers' => \$opt_ignore_numbers);

$preprocess = ($opt_ignore_url || $opt_ignore_numbers || $opt_ignore_latin || $opt_decompose_html_tags);

while (<STDIN>) {
    chomp;
    if ($opt_convert_han_zen) {
        $_ = to_zenkaku($_);
    }

    my $preprocessed = to_hankaku($_);
    if ($preprocess) {
        $preprocessed =~ s{([a-z]+://[~.!*'()A-Za-z0-9;/?:@&=+$,%#_-]+)}{ get_next_nonchar() x length($1); }ge if $opt_ignore_url;
        $preprocessed =~ s{((?:mailto:)?[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:.[a-zA-Z0-9-]+)*)}{ get_next_nonchar() x length($1); }ge  if $opt_ignore_url;
        $preprocessed =~ s{([\d\.,]*[\d\.])}{ get_next_nonchar() x length($1); }ge if $opt_ignore_numbers;
        $preprocessed =~ s{([A-Za-z]+)}{ get_next_nonchar() x length($1); }ge if $opt_ignore_latin;
        $preprocessed =~ s{(<[^>]+>)}{
            my $match = $1;
            $match =~ s{[\x20-\x2f\x3a-\x40\x5b-\x5e\x60\x7b-\x7e]}{
                get_next_nonchar();
            }eg;
            $match;
        }eg if $opt_decompose_html_tags;
    }

    my @chars = split //;
    my @chunks = ();
    
    my $chunk;
    for my $char(@chars) {
        my $last = substr($chunk, -1, 1);
        my $last_type = AbgdData::get_type($last);
        my $char_type = AbgdData::get_type($char);
        if ($last ne '' and not
            (AbgdData::get_script($char) and
             AbgdData::get_script($last) == AbgdData::get_script($char) and
             (($last_type == AbgdData::CORE and $char_type == AbgdData::POST) or
              ($last_type == AbgdData::POST and $char_type == AbgdData::POST) or
              ($last_type == AbgdData::PREV) or
              ($last_type == AbgdData::STACK or $char_type == AbgdData::STACK)))) {
            push @chunks, $chunk;
            $chunk = "";
        }
        $chunk .= $char;
    }
    push @chunks, $chunk if $chunk ne "";
    for (my $i = 0; $i < scalar(@chunks); ++$i) {
        my $pre_chunk = $chunks[$i];
        my $post_chunk = $chunks[$i + 1];
        if ($post_chunk =~ m{(?<![\x{102b}\x{102c}])\x{103a}(?!\x{1039})} and
            AbgdData::get_type($pre_chunk) == AbgdData::get_type($post_chunk)) {
            splice(@chunks, $i, 2, $chunks[$i].$chunks[$i + 1]);
            --$i;
        }
    }

    my $position = 0;
    my $is_first = 1;
    my $prev_preprocessed_char = '';
    for (my $i = 0; $i < scalar(@chunks); ++$i) {
        my $chunk = $chunks[$i];
        my $sp = "";
        if ($chunk =~ m{^[\x20\xa0]$} and $i < scalar(@chunks) - 1) {
            $sp = $chunk;
            ++$i;
            $chunk = $chunks[$i];
        }
        if ($chunk eq "\t") {
            $sp = " ";
            $chunk = " ";
        }
        my $preprocessed_char = substr($preprocessed, $position + length($sp), 1);
        $position += length($sp) + length($chunk);
        my $print_sp = ($is_first or (not $opt_concat and $sp eq "\x20") or ($opt_concat and $sp ne "")) ? " " : "";
        my $correct_label =($is_first or ((not $opt_concat and $sp ne "") or $opt_concat and $sp eq " ")) ? "1" : "0";
        
        my $possible_labels = "0 1";
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
               ($prev_preprocessed_char =~ m{[$nonchar_range]} or
                $preprocessed_char =~ m{[$nonchar_range]})) {
            if ($prev_preprocessed_char eq $preprocessed_char) {
                $possible_labels = "0";
            }
            elsif ($prev_preprocessed_char =~ m{[$nonchar_range]} and
                   $preprocessed_char =~ m{[$nonchar_range]}) {
                $possible_labels = "1";
            }
            else {
                $possible_labels = "0 1";
            }
        }
        
        my %possible_label_dict = ();
        @possible_label_dict{split(/ /, $possible_labels)} = ();
        if (not exists $possible_label_dict{$correct_label}) {
            if ($preprocess) {
                $correct_label = (keys %possible_label_dict)[0];
            }
            else {
                die "Correct label ($correct_label) is not in possible labels ($possible_labels).";
            }
        }

        print join("\t", $print_sp.$chunk, $possible_labels, $correct_label)."\n";
        
        $is_first = 0;
        $prev_preprocessed_char = $preprocessed_char;
    }
    print "\n";
    STDOUT->flush();
}
