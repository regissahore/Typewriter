$^I = ".bak";
while (<>) {
    if (/\A#!/) {
        $_ .= "## Copyright (C) 2014 by ZHG\n";
    }
    print;
}