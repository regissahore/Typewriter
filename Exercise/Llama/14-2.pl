my %last_name = qw {
    fred flintstone Wilma Flintstone Barney Rubble
    betty rubble Bamm-Bamm Rubble PEBBLES FLINTSTONE
};
my @keys = sort {
    if ("\L$last_name{$a}" cmp "\L$last_name{$b}") {
        "\L$a" cmp "\L$b";
    }
    "\L$last_name{$a}" cmp "\L$last_name{$b}";
} keys %last_name;
foreach (@keys) {
    print "$last_name{$_} $_\n";
}