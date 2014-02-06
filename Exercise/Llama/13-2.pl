chomp (my $dir = <STDIN>);
unless ($dir =~ /\A\s*\Z/) {
    chdir $dir;
}
my @files = <.* *>;
foreach (@files) {
    print "$_\n";
}