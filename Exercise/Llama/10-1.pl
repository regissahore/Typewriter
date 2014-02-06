$num = int(1 + rand 100);
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