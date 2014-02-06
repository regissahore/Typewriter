foreach my $file (@ARGV) {
    print "$file ";
    unless (-e $file) {
        print "does not exist.";
    } else {
        if (-r _) {
            print "readable ";
        }
        if (-w _) {
            print "writable ";
        }
        if (-x _) {
            printf "executable ";
        }
    }
    print "\n";
}