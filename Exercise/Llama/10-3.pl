use 5.010;
my $debug = $ENV{DEBUG};
my $num = int(1 + rand 100);
print "$num\n" if $debug;
while (<STDIN>) {
    chomp;
    if ($_ == "quit" || $_ == "exit" || $_ == $num) {
        last;
    } elsif ($_ > $num) {
        print "Too hight\n";
    } else {
        print "Too low\n";
    }
}