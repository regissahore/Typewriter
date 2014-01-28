my %count;
chomp(@lines = <STDIN>);
foreach $line (@lines) {
    $count{$line} += 1;
}
foreach $key (sort keys %count) {
    print $key . " " . $count{$key} . "\n";
}