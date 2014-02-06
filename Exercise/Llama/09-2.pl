$^I = ".out";
while (<>) {
    chomp;
    s/Fred/Larry/i;
    print "$_\n";
}