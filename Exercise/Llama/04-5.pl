use 5.010;

sub greet {
    state @last;
    my $name = shift;
    if (@last) {
        print "Hi $name! I've seen: @last\n";
    } else {
        print "Hi $name! You are the first one here!\n";
    }
    push(@last, $name);
}
greet("Fred");
greet("Barney");
greet("Wilma");
greet("Betty");