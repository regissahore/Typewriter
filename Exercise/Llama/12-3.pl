foreach my $file (@ARGV) {
    if (-w $file && -r _ && -o _) {
        print %file;
    }
}