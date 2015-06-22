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

sub process_maxent
{
    my ($in, $out, $threshold) = @_;
    
    # read

    my $label_num = read_u32($in);
    my %label_id_map;
    for (0..$label_num - 1) {
        my $str = read_string($in);
        $label_id_map{$str} = $_;
    }

    my $attr_num = read_u32($in);
    my %attr_id_map;
    for (0..$attr_num - 1) {
        my $str = read_string($in);
        $attr_id_map{$str} = $_;
    }
    
    my $feature_num = read_u32($in);
    my %pair_id_map;
    for (0..$feature_num - 1) {
        my $first = read_u32($in);
        my $second = read_u32($in);
        $pair_id_map{join("\t", $first, $second)} = $_;
    }

    my @weights;
    for (1..$feature_num) {
        push @weights, read_double($in);
    }

    # filter

    # generate valid feature list
    my $valid_feature_num = 0;
    my @valid_features;
    for my $weight(@weights) {
        push @valid_features, abs($weight) > $threshold ? $valid_feature_num++ : -1;
    }

    # set valid attribute flags
    
    my @attr_flags;
    for my $pair(keys %pair_id_map) {
        my (undef, $attr_id) = split /\t/, $pair;
        my $feature_id = $pair_id_map{$pair};
        if ($valid_features[$feature_id] != -1) {
            $attr_flags[$attr_id] = 1;
        }
    }
    
    # generate old-new attribute index map
    my $valid_attr_num = 0;
    my @valid_attrs;
    for my $flag(@attr_flags) {
        push @valid_attrs, $flag ? $valid_attr_num++ : -1;
    }

    # filter attr-to-index map
    for my $attr(keys %attr_id_map) {
        my $attr_id = $attr_id_map{$attr};
        my $new_attr_id = $valid_attrs[$attr_id];
        if ($new_attr_id == -1) {
            delete($attr_id_map{$attr});
        }
        else {
            $attr_id_map{$attr} = $new_attr_id;
        }
    }

    # filter the weight list
    for my $id(0..$#weights) {
        my $new_id = $valid_features[$id];
        $weights[$new_id] = $weights[$id] if $new_id != -1;
    }
    $#weights = $valid_feature_num - 1;

    # generate a new pair-to-feature-id map
    my %new_pair_id_map;
    for my $pair(keys %pair_id_map) {
        my $feature_id = $pair_id_map{$pair};
        my ($label_id, $attr_id) = split /\t/, $pair;
        my $new_attr_id = $valid_attrs[$attr_id];
        my $new_feature_id = $valid_features[$feature_id];
        $new_pair_id_map{join("\t", $label_id, $attr_id)} = $new_feature_id if $new_attr_id != -1 and $new_feature_id != -1;
    }

    # write
    
    # labels
    write_u32($out, $label_num);
    my @labels;
    for my $label(keys %label_id_map) {
        $labels[$label_id_map{$label}] = $label;
    }
    for my $label(@labels) {
        write_string($out, $label);
    }

    # attributes
    write_u32($out, $valid_attr_num);
    my @attrs;
    for my $attr(keys %attr_id_map) {
        $attrs[$attr_id_map{$attr}] = $attr;
    }
    for my $attr(@attrs) {
        write_string($out, $attr);
    }

    # pairs
    my @pairs;
    for my $pair(keys %new_pair_id_map) {
        $pairs[$new_pair_id_map{$pair}] = $pair;
    }
    
    write_u32($out, scalar(@weights));
    for my $pair(@pairs) {
        my ($label_id, $attr_id) = split /\t/, $pair;
        write_u32($out, $label_id);
        write_u32($out, $attr_id);
    }

    # weights
    for my $weight(@weights) {
        write_double($out, $weight);
    }
    
    printf "Attributes: %d => %d\n", $attr_num, $valid_attr_num;
    printf "Features: %d => %d\n", $feature_num, $valid_feature_num;
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
