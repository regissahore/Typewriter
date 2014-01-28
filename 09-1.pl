$what = "fred|barney";
while (<>) {
    chomp;
    if (/($what){3}/) {
        print "$_\n";
    }
}