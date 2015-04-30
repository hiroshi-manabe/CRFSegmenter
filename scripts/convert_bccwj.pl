#!/usr/bin/env perl

use strict;
use utf8;

use File::Basename;
use Getopt::Long;

my @possible_output_types = qw(segment postag analyze);
my $core_suw;
my $pos_table;
my $filelist_str;
my $unidic_analyze_path;
my $output_type_str;
my $output_dir;
my %converter_dict = (
    'segment' => \&convert_to_segment,
    'postag' => \&convert_to_postag,
    'analyze' => \&convert_to_analyze
    );

my $options = GetOptions('core_suw=s' => \$core_suw,
                         'filelist=s' => \$filelist_str,
                         'pos_table=s' => \$pos_table,
                         'unidic_analyze=s' => \$unidic_analyze_path,
                         'output_type=s' => \$output_type_str,
                         'output_dir=s' => \$output_dir);

my @output_types = split/,/, $output_type_str;
my @filelists = split/,/, $filelist_str;

if (scalar(@output_types) == 0 or
    (scalar(@output_types) == 1 and $output_types[0] eq 'all')) {
    @output_types = @possible_output_types;
}

my %seidaku_dict = ();
if ($unidic_analyze_path) {
    open my $unidic_in, '<:utf8', $unidic_analyze_path or die "Cannot open: $unidic_analyze_path";
    while (<$unidic_in>) {
        s/[\r\n]+$//;
        my @F = split/\t/;
        $seidaku_dict{join("\t", @F[1..4,6])} = $F[5];
    }
    close $unidic_in;
}

my %pos_dict;
if ($pos_table) {
    open my $pos_table_in, '<:utf8', $pos_table or die "Cannot open: $pos_table";
    while (<$pos_table_in>) {
        s/[\r\n]+$//;
        my @F = split/\t/;
        die "Illegal format: line $. in $pos_table" if scalar(@F) != 2;
        $pos_dict{$F[0]} = $F[1];
    }
    close $pos_table_in;
}

for my $type(@output_types) {
    if ($type eq 'analyze' and scalar(keys(%seidaku_dict)) == 0) {
        print STDERR "unidic_analyze not provided: cannot add voicedness tag.\n";
    }
    if (($type eq 'postag' or $type eq 'analyze') and scalar(keys(%pos_dict)) == 0) {
        die "POS table not provided: cannot convert POS tags.";
    }
    for my $filelist(@filelists) {
        my %file_dict = ();
        open my $out, '>:utf8', $output_dir.'/'.(fileparse($filelist))[0].'.'.$type or die "Cannot open: $output_dir/${filelist}.$type";

        open my $list_in, '<:utf8', $filelist or die "Cannot open: $filelist";
        while (<$list_in>) {
            s/[\r\n]+$//;
            $file_dict{$_} = ();
        }
        close $list_in;

        my $converter = $converter_dict{$type};

        open my $in, '<:utf8', $core_suw or die "Cannot open: $core_suw";
        my $is_first = 1;
        while (<$in>) {
            s/[\r\n]+$//;
            my @F = split/\t/;
            for my $i(17..18) {
                $F[$i] = '*' if $F[$i] eq '';
            }
            next if not exists $file_dict{$F[1]};
            print $out $converter->(\@F, \%seidaku_dict, \%pos_dict, $is_first);
            $is_first = 0;
        }
        close $in;
        print $out ($type eq 'analyze' ? "\n\n" : "\n");
        close $out;
    }
}

sub convert_to_segment
{
    my ($fields, $seidaku_dict, $pos_dict, $is_first) = @_;
    my $space = "";
    if ($fields->[9] eq 'B') {
        if (not $is_first) {
            $space = "\n";
        }
    } else {
        $space = " ";
    }
    $fields->[22] =~ s{<[^>]*>}{}g;
    return $space.$fields->[22]
}

sub convert_to_postag
{
    my ($fields, $seidaku_dict, $pos_dict, $is_first) = @_;
    my $space = "";
    if ($fields->[9] eq 'B') {
        if (not $is_first) {
            $space = "\n";
        }
    } else {
        $space = " ";
    }
    $fields->[22] =~ s{<[^>]*>}{}g;
    my $pos_converted = $pos_dict->{$fields->[16]};
    return $space.$fields->[22].'/'.$pos_converted;
}

sub convert_to_analyze
{
    my ($fields, $seidaku_dict, $pos_dict, $is_first) = @_;
    my $newline = "";
    if ($fields->[9] eq 'B') {
        if (not $is_first) {
            $newline = "\n\n";
        }
    } else {
        $newline = "\n";
    }
    my $goiso = join('-', @{$fields}[12, 13, 15]);
    my $dictstr = join("\t", @{$fields}[16, 18, 17], $goiso, $fields->[24]);
    my $seidaku = $seidaku_dict->{$dictstr} || '*';
    $fields->[22] =~ s{<[^>]*>}{}g;
    my $pos_converted = $pos_dict->{$fields->[16]};
    return $newline.join("\t", $fields->[22].'/'.$pos_converted, @{$fields}[16, 18, 17], $goiso, $seidaku, $fields->[24]);
}
