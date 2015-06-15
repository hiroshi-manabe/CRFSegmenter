#!/usr/bin/env perl

use strict;
use utf8;

use Encode;

my ($file, $threshold) = @ARGV;

open my $in, '<:raw', $file;
open my $out, '>:raw', $file.'.filtered';

my $num_features = read_u32($in);
my @features = ();
my @out_features = ();

for (my $i = 0; $i < $num_features; ++$i) {
    my $feature = {};
    $feature->{str} = read_string($in);
    my $label_len = read_u32($in);
    $feature->{labels} = [];
    for (my $j = 0; $j < $label_len; ++$j) {
        push @{$feature->{labels}}, read_i32($in);
    }
    $feature->{weight} = read_double($in);
    push @features, $feature;
    if (abs($feature->{weight}) > $threshold) {
        push @out_features, $feature;
    }
}

write_u32($out, scalar(@out_features));

for my $feature(@out_features) {
    write_string($out, $feature->{str});
    write_u32($out, scalar(@{$feature->{labels}}));
    for my $label(@{$feature->{labels}}) {
        write_i32($out, $label);
    }
    write_double($out, $feature->{weight});
}

my $num_labels = read_u32($in);
write_u32($out, $num_labels);

my %label_map = ();
for (my $i = 0; $i < $num_labels; ++$i) {
    my $str = read_string($in);
    my $num = read_i32($in);
    $label_map{$str} = $num;
    write_string($out, $str);
    write_i32($out, $num);
}
close $in;
close $out;

printf "%d => %d\n", $num_features, scalar(@out_features);

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
