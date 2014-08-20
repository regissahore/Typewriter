while (<>) {
    chomp;
    if (/(?<word>\b\w*a\b)/) {
        print "Matched: |$`<$&>$'|\n";
        print "'word' contains '$+{word}'\n";
    } else {
        print "No match: |$_|\n";
    }
}