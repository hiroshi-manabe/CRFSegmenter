#!/usr/bin/env perl

use strict;
use utf8;

use Encode;

my %type_proc_dict = (
    'hocrf' => \&process_hocrf,
    'maxent' => \&process_maxent
    );

sub usage
{
    print <<USAGE;
filter_model.pl <file> <type> <threshold>
    <file> : The input model file. The output file will be named "<file>.filtered".
    <type> : "hocrf" for High-Order CRF models and "maxent" for Maximum Entropy models.
    <threshold> : The cutoff threshold. Must be >= 0.
USAGE
    exit();
}

my ($file, $type, $threshold) = @ARGV;
die "File not found: $file" if not -f $file;
usage() if not exists $type_proc_dict{$type};
usage() if $threshold < 0;

open my $in, '<:raw', $file;
open my $out, '>:raw', $file.'.filtered';
$type_proc_dict{$type}->($in, $out, $threshold);
close $out;
close $in;

sub process_hocrf
{
    my ($in, $out, $threshold) = @_;
    
    # read

    # feature templates
    my %ft_map;
    my $num_ft = read_u32($in);
    for (1..$num_ft) {
        my $obs = read_string($in);
        my $label_len = read_u32($in);
        my $key = $obs."\t".$label_len;
        my $f_num = read_u32($in);
        for (1..$f_num) {
            push @{$ft_map{$key}}, read_u32($in);
        }
    }

    # features
    my $num_features = read_u32($in);
    my @weights = ();
    my @label_seq_indexes = ();
    for (1..$num_features) {
        push @weights, read_double($in);
        push @label_seq_indexes, read_u32($in);
    }

    # label sequences
    my $num_label_seqs = read_u32($in);
    my @label_seqs = ();
    for (1..$num_label_seqs) {
        my $len = read_u32($in);
        my @seq;
        for (1..$len) {
            push @seq, read_u32($in);
        }
        push @label_seqs, \@seq;
    }

    # label strings
    my $num_labels = read_u32($in);
    my @labels = ();
    for (1..$num_labels) {
        push @labels, read_string($in);
    }

    # filter
    
    # features
    my $num_valid_features = 0;
    my @valid_features = ();
    my @seq_valid_flags = ();
    
    for (0..$#weights) {
        if (abs($weights[$_]) > $threshold) {
            $seq_valid_flags[$label_seq_indexes[$_]] = 1;
            $weights[$num_valid_features] = $weights[$_];
            $label_seq_indexes[$num_valid_features] = $label_seq_indexes[$_];
            push @valid_features, $num_valid_features;
            ++$num_valid_features;
        } else {
            push @valid_features, -1;
        }
    }
    
    $#weights = $num_valid_features - 1;
    $#label_seq_indexes = $num_valid_features - 1;
    
    # label seq list
    my $num_valid_seqs = 0;
    my @valid_seq_list = ();

    for (0..$#label_seqs) {
        if ($seq_valid_flags[$_]) {
            push @valid_seq_list, $num_valid_seqs;
            $label_seqs[$num_valid_seqs] = $label_seqs[$_];
            ++$num_valid_seqs;
        } else {
            push @valid_seq_list, -1;
        }
    }
    $#label_seqs = $num_valid_seqs - 1;
    
    # update features
    for (0..$#label_seq_indexes) {
        $label_seq_indexes[$_] = $valid_seq_list[$label_seq_indexes[$_]];
    }

    # trim feature templates
    my %new_ft_map = ();
    for my $key(keys %ft_map) {
        my $values = $ft_map{$key};
        my @new_values = ();
        for my $v(@{$values}) {
            my $new_index = $valid_features[$v];
            push @new_values, $new_index if $new_index != -1;
        }
        $new_ft_map{$key} = \@new_values if scalar(@new_values) != 0;
    }

    # write

    # feature templates
    write_u32($out, scalar(keys %new_ft_map));
    for my $ft(keys %new_ft_map) {
        my ($obs, $len) = split/\t/, $ft;
        write_string($out, $obs);
        write_u32($out, $len);
        write_u32($out, scalar @{$new_ft_map{$ft}});
        for my $i(@{$new_ft_map{$ft}}) {
            write_u32($out, $i);
        }
    }

    # features
    write_u32($out, scalar(@weights));
    for (0..$#weights) {
        write_double($out, $weights[$_]);
        write_u32($out, $label_seq_indexes[$_]);
    }

    # label sequences
    write_u32($out, scalar(@label_seqs));
    for my $label_seq(@label_seqs) {
        write_u32($out, scalar(@{$label_seq}));
        for my $l(@{$label_seq}) {
            write_u32($out, $l);
        }
    }
    
    # label strings
    write_u32($out, scalar(@labels));
    for my $label(@labels) {
        write_string($out, $label);
    }

    printf "Feature templates: %d => %d\n", $num_ft, scalar(keys %new_ft_map);
    printf "Features: %d => %d\n", $num_features, $num_valid_features;
    printf "Label sequences: %d => %d\n", $num_label_seqs, $num_valid_seqs;
}

sub read_i32
{
    my ($in) = @_;
    my $buf;
    read($in, $buf, 4);
    my $val = unpack('V', $buf);
    return $val & 0x80000000 ? -((~$val & 0xffffffff) + 1) : $val;
}

sub read_u32
{
    my ($in) = @_;
    my $buf;
    read($in, $buf, 4);
    return unpack('V', $buf);
}

sub read_double
{
    my ($in) = @_;
    my $buf;
    read($in, $buf, 8);
    return unpack('d', $buf);
}

sub read_string
{
    my ($in) = @_;
    my $len = read_u32($in);
    my $buf;
    read ($in, $buf, $len);
    return decode_utf8($buf);
}

sub write_i32
{
    my ($out, $val) = @_;
    my $buf = pack('V', $val & 0xffffffff);
    print $out $buf;
}

sub write_u32
{
    my ($out, $val) = @_;
    my $buf = pack('V', $val);
    print $out $buf;
}

sub write_double
{
    my ($out, $val) = @_;
    my $buf = pack('d', $val);
    print $out $buf;
}

sub write_string
{
    my ($out, $str) = @_;
    my $raw = encode_utf8($str);
    write_u32($out, length($raw));
    print $out $raw;
}
