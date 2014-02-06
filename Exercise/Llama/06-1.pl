my %last_name = (
    "fred" => "flintstone",
    "barney" => "rubble",
    "wilma" => "flintstone",
);
chomp(my $first_name = <STDIN>);
print $last_name{$first_name} . "\n";