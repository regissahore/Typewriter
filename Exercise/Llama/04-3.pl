sub total {
    my($sum) = shift(@_);
    foreach (@_) {
        $sum += $_;
    }
    $sum;
}
sub average {
    &total(@_) / @_;
}
sub above_average {
    my @above = ();
    $average = &average;
    foreach (@_) {
        if ($_ > $average) {
            push(@above, $_);
        }
    }
    @above;
}
my @fred = above_average(1..10);
print "\@fred is @fred\n";
print "(Should be 6 7 8 9 10)\n";
my @barney = above_average(100, 1..10);
print "\@barney is @barney\n";
print "(Should be just 100)\n";