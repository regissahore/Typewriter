use 5.010;
$num = int(1 + rand 100);
while (<STDIN>) {
    chomp;
    given ($_) {
        when ($_ == "quit" || $_ == "exit" || $_ == $num) {
            last;
        } 
        when ($_ > $num) {
            print "Too hight\n";
        } 
        default {
            print "Too low\n";
        }
    }
}