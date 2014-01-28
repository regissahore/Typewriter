my $oldest_name = shift @ARGV;
my $oldest_time = -M $oldest_name;

foreach (@ARGV) {
    my $time = -M;
    if ($time > $oldest_time) {
        ($oldest_name, $oldest_time) = ($_, $time);
    }
}
print "$oldest_name $oldest_time\n";