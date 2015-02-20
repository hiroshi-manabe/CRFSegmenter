my $in_file = "Scripts.txt";
my $out_file = "script_data.h";

open my $in, '<', $in_file;

my @arr = ();
my %map = ('' => 0);

while (<$in>) {
    next unless m{^([0-9A-F]+)(?:\.\.([0-9A-F]+))?\s*;\s*(\S+)};
    $map{uc($3)} = scalar(keys %map) if not exists $map{$3};
    $start = hex($1);
    $end = $2 ? hex($2) : $start;
    next if $start >= 0xe0000;
    for ($start..$end) {
        $arr[$_] = uc($3);
    }
}

my @script_arr = ();

for (keys %map) {
    $script_arr[$map{$_}] = $_;
}

my $max_script = $#script_arr;
my $max_code_point = $#arr;

open my $out, '>', $out_file;
print $out <<HERE;
#ifndef SEGMENTER_SCRIPT_DATA_H_
#define SEGMENTER_SCRIPT_DATA_H_

#include <cstdint>
#include <string>

namespace Segmenter {

namespace ScriptData {

using std::string;

typedef unsigned char script_type_t;

#define SEGMENTER_SCRIPT_DATA_MAX_SCRIPT $max_script
#define SEGMENTER_SCRIPT_DATA_MAX_CODEPOINT $max_code_point

const char *SCRIPT_STRING_TABLE[] = {
HERE
for (0..$#script_arr) {
    my $comma = $_ == $#script_arr ? '' : ',';
    my $str = $_ == 0 ? "Undefined" : $_;
    print $out qq{    "$script_arr[$_]"$comma\n};
}

print $out <<HERE;
};
script_type_t SCRIPT_TABLE[] = {
HERE

for (0..$#arr) {
    my $comma = $_ == $#arr ? '' : ',';
    my $space = $_ % 16 == 0 ? "\n    " : " ";
    print $out "$space$map{$arr[$_]}$comma";
}

print $out <<HERE;
};

string scriptToScriptString(script_type_t script) {
    if (script > SEGMENTER_SCRIPT_DATA_MAX_SCRIPT) {
        return SCRIPT_STRING_TABLE[0];
    }
    return string(SCRIPT_STRING_TABLE[script]);
}

script_type_t codePointToScript(uint32_t codePoint) {
    if (codePoint > SEGMENTER_SCRIPT_DATA_MAX_CODEPOINT) {
        return 0;
    }
    return SCRIPT_TABLE[codePoint];
}

string codePointToScriptString(uint32_t codePoint) {
    return scriptToScriptString(codePointToScript(codePoint));
}

}  // namespace ScriptData

}  // namespace Segmenter
#endif  // SEGMENTER_SCRIPT_DATA_H_
HERE
