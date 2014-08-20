use 5.010;
for (1 .. 105) {
    given ($_) {
        when (not $_ % 3) {print "Fizz "; continue;}
        when (not $_ % 5) {print "Buzz "; continue;}
        when (not $_ % 7) {print "Sausage ";}
    }
    print "\n";
}