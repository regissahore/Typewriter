chomp (my $dir = <STDIN>);
unless ($dir =~ /\A\s*\Z/) {
    chdir $dir;
}
opendir cur, ".";
foreach (readdir cur) {
    print "$_\n";
}