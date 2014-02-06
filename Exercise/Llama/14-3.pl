$input = "Thisisatest.";
$sub = "is";
for (my $pos = -1;;) {
    $pos = index($input, $sub, $pos + 1);
    last if $pos == -1;
    print $pos . " ";
}
print "\n";