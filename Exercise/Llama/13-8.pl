foreach (glob('.* *')) {
    my $dst = readlink $_;
    if (defined($dst)) {
        print "$_\n";
    }
}