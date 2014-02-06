use POSIX qw(strftime);
foreach my $file (glob('*')) {
    my ($atime, $mtime) = map {
        strftime('%Y-%m-%d', localtime($_));
    } (stat $file)[8, 9];
    printf "%-20s %10s %10s\n", $file, $atime, $mtime;
}