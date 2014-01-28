my $filename = 'test';
open my $file, '<', $filename;
chomp(my @strings = <FILE>);
while (1) {
    chomp(my $pattern = <STDIN>);
    last if $pattern =~ /\A\s*\Z/;
    my @matches = eval {
        grep /$pattern/, @strings;
    };
    unless ($@) {
        my $count = @matches;
        print map "$_\n", @matches;
    }
    print "\n";
}