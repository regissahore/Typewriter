use 5.010;
sub divisors {
    my $number = shift;
    my @divisors = ();
    foreach my $divisor (2 .. ($number / 2)) {
        push @divisors, $divisor unless $number % $divisor;
    }
    @divisors;
}
given(<STDIN>) {
    when (!/\A\d+\Z/) {say "Invalid.";}
    my @divisors = divisors($_);
    my @empty;
    when (@divisors ~~ @empty) {say "Prime.";}
    default {say join " ", @divisors}
}