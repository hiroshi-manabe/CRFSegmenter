#!/usr/bin/env perl

use strict;
use utf8;

use Getopt::Long;

my @possible_output_types = qw(segment postag analyze);
my $pos_table;
my $ipadic_path;
my $output_type_str;
my $output_dir;
my %converter_dict = (
    'segment' => \&convert_to_segment,
    'postag' => \&convert_to_postag,
    'analyze' => \&convert_to_analyze,
    );

my $options = GetOptions('ipadic_path=s' => \$ipadic_path,
                         'pos_table=s' => \$pos_table,
                         'output_type=s' => \$output_type_str,
                         'output_dir=s' => \$output_dir);

my @output_types = split/,/, $output_type_str;
if (scalar(@output_types) == 0 or
    (scalar(@output_types) == 1 and $output_types[0] eq 'all')) {
    @output_types = @possible_output_types;
}

my %pos_dict;
if ($pos_table) {
    die "pos_table not found: $pos_table" if not -f $pos_table;
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
    if (($type eq 'postag' or $type eq 'analyze') and scalar(keys(%pos_dict)) == 0) {
        die "POS table not provided: cannot convert POS tags.";
    }
    open my $ipadic_in, '<:utf8', $ipadic_path or die "Cannot open the file: $ipadic_path";
    open my $out, '>:utf8', $output_dir.'/ipadic.'.$type;
    my $converter = $converter_dict{$type};
    
    while (<$ipadic_in>) {
        chomp;
        my @F = split/\t/;
        print $out $converter->(\@F, \%pos_dict)."\n";
    }
    
    close $ipadic_in;
    close $out;
}

sub get_char_type
{
    my ($orth) = @_;
    return ($orth =~ m{^[\p{Hiragana}ー]+$} ? '平' :
            $orth =~ m{^[\p{Katakana}ー]+$} ? '片' :
            $orth =~ m{^\p{Han}+$} ? '漢' :
            $orth =~ m{^\p{Latin}+$} ? '英' :
            $orth =~ m{^\p{Digit}+$} ? '数' :
            $orth =~ m{[^\p{Alnum}]+$} ? '記' :
            '混');
}

sub get_pos
{
    my ($fields) = @_;
    return join('-', grep {$_ ne '*'} @{$fields}[4..7]);
}

sub get_goiso
{
    my ($fields) = @_;
    return join('-', grep {$_ ne '*'} @{$fields}[11, 10, 16]);
}

sub convert_to_segment
{
    my ($fields, $pos_dict) = @_;
    my $count = 0;
    return join("\t", $fields->[0], map { $count++ . "-" . $_ }
                '単語', length($fields->[0]),
                $pos_dict->{get_pos($fields)},
                @{$fields}[9, 10], get_char_type($fields->[0]));
}

sub convert_to_postag
{
    my ($fields, $pos_dict) = @_;
    return join("\t", $fields->[0], $pos_dict->{get_pos($fields)});
}

sub convert_to_analyze
{
    my ($fields, $pos_dict) = @_;
    my $pos = get_pos($fields);
    return join("\t", $fields->[0]."/".$pos_dict->{$pos}, $pos, @{$fields}[9, 8,10,11,12]);
}
