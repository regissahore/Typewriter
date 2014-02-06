chomp(@lines = <STDIN>);
foreach $line (@lines) {
    print $line . " ";
}
print "\n";
while (my($index, $value) = each @lines) {
    print $value . "\n";
}