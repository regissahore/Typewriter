use 5.010;

sub greet {
    state $last;
    my $name = shift;
    if (defined $last) {
        print "Hi $name! $last is also here!\n";
    } else {
        print "Hi $name! You are the first one here!\n";
    }
    $last = $name;
}
greet("Fred");
greet("Barney");