#!/usr/bin/env perl
use strict;
use utf8;
use open "IO" => ":utf8";
use open ":std";

use File::Basename;
use FindBin;
use Getopt::Long qw(:config bundling posix_default no_ignore_case);

my $DEFAULT_CFORMS_FILE = "./cforms.tsv";
my $DEFAULT_POS_TABLE_FILE = "./pos_table_ipadic.tsv";
my $TEMP_EXT = ".temp";
my $file_dir = dirname(__FILE__);

sub usage {
    print <<USAGE;
usage: $FindBin::Script [--cforms-file <path to cforms file>] [--pos-table-file <path to POS table file>] --prefix <output file prefix> [-d|--dict <path to a dictionary]... [-c|--concat-dict <path to a concatenation dictionary]...
USAGE
    exit(0);
}

sub close_files {
    my ($ref) = @_;
    for my $type(keys %{$ref}) {
        close $ref->{$type}->{"handle"};
        unlink $ref->{$type}->{"file"}.$TEMP_EXT;
    }
}

sub main {
    my %opts;
    GetOptions(
        \%opts,
        "cforms-file=s",
        "pos-table-file",
        "dict|d=s@",
        "concat-dict|c=s@",
        "prefix=s",
        );
    my @required = qw(prefix);
    usage() if grep { not exists $opts{$_}; } @required;

    my $config_ref = {};
    my $script_dir = dirname(__FILE__);
    require "${script_dir}/analyze.config.pl";
    config::get_config($config_ref);

    my %output_dict = (
        "output-types" => {
            "segment" => {"proc" => \&output_segment_dict},
            "postag" => {"proc" => \&output_postag_dict},
            "morph" => {"proc" => \&output_morph_dict},
            "concat" => {"proc" => \&output_concat_dict}
        },
        "prefix" => $opts{"prefix"}
        );

    my %cforms_dict;
    my %pos_dict;

    my $cforms_file = $opts{"cforms-file"} || $config_ref->{"CFORMS_FILE"};
    open IN, "<", $cforms_file or die "Cannot open cforms file: $opts{'cforms-file'}";
    while (<IN>) {
        chomp;
        my @F = map { $_ eq "*" ? "" : $_ } split /\t/;
        $cforms_dict{$F[0]}{$F[1]} = [@F[2, 3, 4]];
    }
    close IN;

    my $pos_table_file = $opts{"pos-table-file"} || $config_ref->{"POS_TABLE_FILE"};
    open IN, "<", $pos_table_file or die "Cannot open POS table file: $config_ref->{POS_TABLE_FILE}";
    while (<IN>) {
        chomp;
        my @F = split /\t/;
        $pos_dict{$F[0]} = $F[1];
    }
    close IN;

    for my $type(keys %{$output_dict{"output-types"}}) {
        my $filename = $output_dict{"prefix"}.".$type";
        $output_dict{"output-types"}{$type}{"file"} = $filename;
        open $output_dict{"output-types"}{$type}{"handle"}, ">", $filename.$TEMP_EXT or die;
    }

    my %output_set;
    %output_set = ();
    @output_set{qw(segment postag morph)} = ();

    my $dup_dict;

    %output_set = ();
    @output_set{qw(segment postag morph)} = ();
    for my $file(@{$opts{"dict"}}) {
        open IN, "<", $file or close_files($output_dict{"output-types"}); die "Cannot open: $file";
        while (<IN>) {
            chomp;
            my @F = split /\t/;
            if ($F[3] eq "*") {
                output($output_dict{"output-types"}, \%output_set, \%pos_dict, [@F[4, 2], "*", "*", @F[0, 1, 4, 0, 1, 5]]);
            }
            else {
                my @refs = (\@F);
                if ($F[3] =~ m{^五段} and $F[2] ne "助動詞") {
                    my @G = @F;
                    $G[3] = "一段";
                    for my $i(0..1) {
                        $G[$i] =~ s{(.)$}{ die unless ($a=$1)=~tr/ウクスツヌフムルグズヅブプ/エケセテネヘメレゲゼデベペ/; $a."ル"; }e;
                    }
                    $G[4] =~ s{(.)$}{ die unless ($a=$1)=~tr/うくすつぬふむるぐずづぶぷ/えけせてねへめれげぜでべぺ/; $a."る";}e;
                    $G[5]  .= "-可能動詞";
                    push @refs, \@G;
                }
                for my $ref(@refs) {
                    my @orig = @{$ref};
                    die "Nonexistent form: $ref->[3]" if not exists $cforms_dict{$ref->[3]};
                    my $basic_ref = $cforms_dict{$ref->[3]}{"基本形"};
                    die "Basic form does not match (kana): $ref->[0] $basic_ref->[1]" if $ref->[0] !~ s{\Q$basic_ref->[1]\E$}{};
                    die "Basic form does not match (pronunciation): $ref->[1] $basic_ref->[2]" if $ref->[1] !~ s{\Q$basic_ref->[2]\E$}{};
                    my $basic_len = length($basic_ref->[0]);
                    my $kanji_len = 0;
                    $kanji_len++ while $basic_len and substr($ref->[4], -$basic_len + $kanji_len) ne substr($basic_ref->[0], $kanji_len);
                    substr($ref->[4], -$basic_len + $kanji_len, $basic_len - $kanji_len, "");
                    my $cforms_ref = $cforms_dict{$ref->[3]};
                    for my $form(sort keys %{$cforms_ref}) {
                        my $form_ref = $cforms_ref->{$form};
                        output($output_dict{"output-types"}, \%output_set, \%pos_dict, [$ref->[4].substr($form_ref->[0], $kanji_len), @{$ref}[2, 3], $form, $ref->[0].$form_ref->[1], $ref->[1].$form_ref->[2], @orig[4, 0, 1], $ref->[5]]);
                    }
                }
            }
        }
    }

    %output_set = ();
    @output_set{qw(concat)} = ();
    if ($opts{"concat-dict"}) {
        for my $file(@{$opts{"concat-dict"}}) {
            open IN, "<", $file;
            while (<IN>) {
                chomp;
                my @F = split /\t/;
                output($output_dict{"output-types"}, \%output_set, \%pos_dict, [@F[3, 2], "*", "*", @F[0, 1, 3, 0, 1, 4]]);
            }
            close IN;
        }
    }

    my $output_types = $output_dict{"output-types"};
    for my $type(keys %{$output_types}) {
        next if not exists $output_types->{$type}{"handle"};
        close $output_types->{$type}{"handle"} ;
        system("$config_ref->{DICTIONARY_CONVERTER} -o $output_types->{$type}{'file'} < $output_types->{$type}{'file'}$TEMP_EXT");
        unlink $output_types->{$type}{"file"}.$TEMP_EXT;
    }
}

sub output
{
    my ($output_dict_ref, $output_set_ref, $pos_dict_ref, $content) = @_;
    for my $type(keys %{$output_set_ref}) {
        die "Undefined type: $type" if not exists $output_dict_ref->{$type}{"proc"};
        next if not exists $output_dict_ref->{$type}{"handle"};
        my $handle = $output_dict_ref->{$type}{"handle"};
        my $output_ref = $output_dict_ref->{$type}{"proc"}($pos_dict_ref, $content);

        for my $output(@{$output_ref}) {
            next if exists $output_dict_ref->{$type}{"dup"}{$output};
            print {$handle} $output."\n";
            $output_dict_ref->{$type}{"dup"}{$output} = ();
        }
        ++$output_dict_ref->{$type}{"counter"};
    }
}

sub output_segment_dict
{
    my ($pos_dict_ref, $r) = @_;
    my $count = 1;
    my @fields = @{$r};
    return [join("\t", $fields[0], "0-単語", map { $count++."-".$_ } @fields[0, 1, 2, 3, 9])];
}

sub output_postag_dict
{
    my ($pos_dict_ref, $r) = @_;
    die "Nonexistent POS: $r->[1]" if not exists $pos_dict_ref->{$r->[1]};
    my $ret = [join("\t", $r->[0], $pos_dict_ref->{$r->[1]})];
    push @{$ret}, join("\t", $r->[0], "名詞-数") if $r->[1] ne "名詞-数" and $r->[0] =~ m{^[何幾数]?[一二三四五六七八九〇十百千万億兆１２３４５６７８９０]{2,}$} and $r->[0] !~ m{[十百]千|(^|[万億兆])[〇万億兆]};
    return $ret;
}

sub output_morph_dict
{
    my ($pos_dict_ref, $r) = @_;
    die "Nonexistent POS: $r->[1]" if not exists $pos_dict_ref->{$r->[1]};
    return [join("\t", $r->[0]."/".$pos_dict_ref->{$r->[1]}, @{$r}[1, 3, 2, 9, 4..8])];
}

sub output_concat_dict
{
    my ($pos_dict_ref, $r) = @_;
    die "Nonexistent POS: $r->[1]" if not exists $pos_dict_ref->{$r->[1]};
    return [join("\t", $r->[0], $pos_dict_ref->{$r->[1]}, @{$r}[1, 3, 2, 9, 4..8])];
}

main();
