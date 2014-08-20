my %visit;
foreach (@ARGV) {
    $visit{$_} = 1;
}
while (<>) {
    if (/\A## Copyright/) {
        delete $visit{$ARGV};
    }
}
@ARGV = sort keys %visit;
$^I = ".bak";
while (<>) {
    if (/\A#!/) {
        $_ .= "## Copyright (C) 2014 by ZHG\n";
    }
    print;
}