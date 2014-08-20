use DateTime;
my $time = localtime;
my $now = DateTime->new(
    year    => $time[5] + 1900,
    month   => $time[4] + 1,
    day     => $time[3],
);
my $input = DateTime->new(
    year    => $ARGV[0],
    month   => $ARGV[1],
    day     => $ARGV[2],
);
my $duration = $now - $input;
print "%d years, %d months, and %d days\n", $duration->in_units(qw(years months days));