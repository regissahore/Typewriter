sub total {
    ($sum) = shift(@_);
    foreach (@_) {
        $sum += $_;
    }
    $sum;
}
print &total(1..1000);