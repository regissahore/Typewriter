@names = qw(fred betty barney dino wilma pebbles bamm-bamm);
chomp(@lines = <STDIN>);
foreach $line (@lines) {
    print @names[$line - 1] . " "
}