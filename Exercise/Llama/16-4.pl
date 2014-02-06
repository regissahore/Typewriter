use 5.010;
sub hup {state $n; say 'HUP: ', ++$n}
sub usr1 {state $n; say 'USR1: ', ++$n}
sub usr2 {state $n; say 'USR2: ', ++$n}
foreach my $signal (sq(int hup usr1 usr2)) {
    $SIG{uc $signal} = "${signal}";
}
while (1) {
    sleep 1;
}