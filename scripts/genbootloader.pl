#!/usr/bin/perl
use strict;

my @targets = splice @ARGV;

my @mainfns = map { "_main_$_" } @targets;
my $mainfnsstr = join(", ", map { "$_(void)" } @mainfns);
my $mainswitch = '';
my $defaultmain = $mainfns[0];

my $mainarray = "mainfn mainfns[" . scalar(@mainfns) . "] = {\n";
$mainarray .= join(",\n", map { "    \&$_" } @mainfns) . "\n};";

my $nummainfns = scalar @mainfns;

while (<>) {
    s,\@\@DEFAULT_MAIN_FUNCTION\@\@,$defaultmain,g;
    s,\@\@MAIN_FUNCTIONS\@\@,$mainfnsstr,g;
    s,\@\@NUM_MAIN_FUNCTIONS\@\@,$nummainfns,g;
    s,\@\@MAIN_SWITCH\@\@,$mainswitch,g;
    s,\@\@MAIN_ARRAY\@\@,$mainarray,g;
    print;
}
