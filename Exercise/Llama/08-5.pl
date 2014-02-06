while (<>) {
    chomp;
    if (/(?<word>\b\w*a\b)(?<after>.{0,5})/xs) {
        print "Matched: |$`<$&>$'|\n";
        print "'word' contains '$+{word}'\n";
        print "'after' contains '$+{after}'\n";
    } else {
        print "No match: |$_|\n";
    }
}