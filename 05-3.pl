chomp(@lines = <STDIN>);
chomp(@width = <STDIN>);
print ("1234567890" x (($width + 9) / 10)), "\n";
foreach (@lines) {
    printf "%${width}s\n", $_;
}