#!/usr/bin/env perl

use strict;
use utf8;

use File::Basename;
use Getopt::Long qw(:config posix_default no_ignore_case gnu_compat);

my @possible_output_types = qw(segment postag analyze);
my $pos_table;
my $filelist_str;
my $output_type_str;
my $output_dir;
my %converter_dict = (
    'segment' => \&convert_to_segment,
    'postag' => \&convert_to_postag,
    'analyze' => \&convert_to_analyze
    );

my $options = GetOptions('filelist=s' => \$filelist_str,
                         'pos_table=s' => \$pos_table,
                         'output_type=s' => \$output_type_str,
                         'output_dir=s' => \$output_dir);

my @output_types = split/,/, $output_type_str;
my @filelists = split/,/, $filelist_str;

if (scalar(@output_types) == 0 or
    (scalar(@output_types) == 1 and $output_types[0] eq 'all')) {
    @output_types = @possible_output_types;
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
    if (scalar(keys(%pos_dict)) == 0) {
        die "POS table is empty: cannot convert POS tags.";
    }
}

for my $type(@output_types) {    
    for my $filelist(@filelists) {
        my %file_dict = ();
        my $converter = $converter_dict{$type};

        open my $out, '>:utf8', $output_dir.'/'.(fileparse($filelist))[0].'.'.$type or die "Cannot open: $output_dir/${filelist}.$type";
        open my $filelist_in, '<:utf8', $filelist;
        while (my $file = <$filelist_in>) {
            $file =~ s/[\r\n]+$//;
            open my $in, '<:utf8', $file or die "Cannot open: $file";
            my $is_first = 1;
            while (<$in>) {
                s/[\r\n]+$//;
                my @F = split/\t/;
                my @E = split/,(?![^"]+"(?:,|$))/, $F[1];
                unshift @E, $F[0];
                map { s/^"//; s/"$//; } @E;
                print $out $converter->(\@E, \%pos_dict, \$is_first);
            }
            close $in;
        }
        close $out;
    }
}

sub get_pos
{
    my ($fields) = @_;
    return join('-', grep {$_ ne '*'} @{$fields}[1..4]);
}

sub convert_to_segment
{
    my ($fields, $pos_dict, $is_first) = @_;
    my $space = "";
    if (scalar(@${fields}) == 1 and $fields->[0] eq 'EOS') {
        ${$is_first} = 1;
        return "\n";
    }
    else {
        if (not ${$is_first}) {
            $space = " ";
        }
        else {
            ${$is_first} = 0;
        }
    }
    return $space.$fields->[0]
}

sub convert_to_postag
{
    my ($fields, $pos_dict, $is_first) = @_;
    my $space = "";
    if (scalar(@{$fields}) == 1 and $fields->[0] eq 'EOS') {
        ${$is_first} = 1;
        return "\n";
    } else {
        if (not ${$is_first}) {
            $space = " ";
        }
        else {
            ${$is_first} = 0;
        }
    }
    my $pos_converted = $pos_dict->{get_pos($fields)};
    return $space.$fields->[0].'/'.$pos_converted;
}

sub convert_to_analyze
{
    my ($fields, $pos_dict, $is_first) = @_;
    my $newline = "";
    if (scalar(@{$fields}) == 1 and $fields->[0] eq 'BOS') {
        return "\n";
    }
    my $pos = get_pos($fields);
    my $pos_converted = $pos_dict->{$fields->[16]};
    return $newline.join("\t", $fields->[0].'/'.$pos_converted, @{$fields}[6,5,7,8,9]);
}
