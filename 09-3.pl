while (<>) {
    chomp;
    s/Fred/\n/i;
    s/Wilma/Fred/i;
    s/\n/Wilma/i;
    print "$_\n";
}