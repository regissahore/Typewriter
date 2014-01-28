chomp(@lines = <STDIN>);
print ("1234567890" x 6);
print "\n";
foreach (@lines) {
    printf "%20s\n", $_;
}