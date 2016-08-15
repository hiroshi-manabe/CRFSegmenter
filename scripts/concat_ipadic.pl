#!/usr/bin/env perl

use strict;
use utf8;

use Getopt::Long qw(:config posix_default no_ignore_case gnu_compat);

my $ipadic_dir;
my $output_filename;

my $options = GetOptions('ipadic_dir=s' => \$ipadic_dir,
                         'output_filename=s' => \$output_filename);

opendir my $ipadic_dir_in, $ipadic_dir or die "Cannot open directory: $ipadic_dir";
open my $out, '>:utf8', $output_filename;

while (my $file = readdir($ipadic_dir_in)) {
    next unless $file =~ /\.csv$/;
    open my $in, '<:encoding(euc-jp)', $ipadic_dir.'/'.$file;
    while (<$in>) {
        s/[\r\n]+$//;
        my @F = split/,/;
        print $out join("\t", @F)."\n";
    }
    close $in;
}
close $out;
closedir $ipadic_dir_in;
