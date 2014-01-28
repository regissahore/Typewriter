my $max_length;
foreach $key (keys %ENV) {
    my $length = length($key);
    if ($length > $max_length) {
        $max_length = $length;
    }
}
foreach $key (sort keys %ENV) {
    printf "%-${max_length}s %s\n", $key, $ENV{$key};
}