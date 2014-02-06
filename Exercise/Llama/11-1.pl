use Module::CoreList;
my %modules = %{ $Module::CoreList::version{5.014} };
print join "\n", keys %modules;